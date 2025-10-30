#include <systemc.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

#include "delay_n.cpp"
#include "gamma_sum.cpp"
#include "phi_sum.cpp"

double binToDouble(const std::string& bin_str, int total_bits, int integer_bits, bool is_signed) {
    if (bin_str.length() != total_bits) {
        throw std::runtime_error("ERR: bin len mismatch (expected " + std::to_string(total_bits) + ", got " + std::to_string(bin_str.length()) + ") for: " + bin_str);
    }
    if (total_bits <= 0) {
         throw std::runtime_error("ERR: total_bits must be positive.");
    }

    long long raw_val = 0;
    try {
        size_t processed_chars = 0;
        raw_val = std::stoll(bin_str, &processed_chars, 2);
        if (processed_chars != bin_str.length()) {
             throw std::runtime_error("ERR: Invalid char found by stoll in: " + bin_str);
        }
    } catch (const std::invalid_argument& ia) {
        throw std::runtime_error("ERR: Invalid binary string format: " + bin_str);
    } catch (const std::out_of_range& oor) {
         std::cerr << "WARN: Binary string potentially out of range for long long, conversion might be inaccurate: " << bin_str << std::endl;
         try {
             raw_val = std::stoull(bin_str, nullptr, 2);
         } catch (...) {
              throw std::runtime_error("ERR: Binary string out of range: " + bin_str);
         }
    }


    double result = 0.0;
    int fractional_bits = total_bits - integer_bits - (is_signed ? 1 : 0);
    if (fractional_bits < 0 || integer_bits < 0 || (is_signed && total_bits < 1)) {
        throw std::runtime_error("ERR: Invalid fixed-point format params (WL=" + std::to_string(total_bits) + ", IWL=" + std::to_string(integer_bits) + ", signed=" + std::to_string(is_signed) + ")");
    }
    if (total_bits > 63 && raw_val == std::numeric_limits<long long>::max()) {
         std::cerr << "WARN: raw_val hit max long long, precision loss possible." << std::endl;
    }


    double scale = std::pow(2.0, fractional_bits);
    if (scale == 0) scale = 1.0;

    if (is_signed) {
        long long sign_bit_val = 1LL << (total_bits - 1);
        if ((raw_val & sign_bit_val) != 0) {
            long long signed_val = raw_val - (1LL << total_bits);
            result = static_cast<double>(signed_val) / scale;
        } else {
            result = static_cast<double>(raw_val) / scale;
        }
    } else {
        result = static_cast<double>(raw_val) / scale;
    }

    return result;
}


SC_MODULE(top_testbench) {

    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<double> r_in_real_sig;
    sc_signal<double> r_in_imag_sig;
    sc_signal<double> p_in_sig;

    sc_signal<double> r_out_real_sig;
    sc_signal<double> r_out_imag_sig;
    sc_signal<double> r_delayed_out_real_sig;
    sc_signal<double> r_delayed_out_imag_sig;
    sc_signal<bool> valid_from_delay_sig;

    sc_signal<double> gamma_out_real_sig;
    sc_signal<double> gamma_out_imag_sig;
    sc_signal<bool> valid_from_gamma_sig;

    sc_signal<double> phi_out_sig;
    sc_signal<bool> valid_from_phi_sig;

    delay_n *dut_delay;
    gamma_sum *dut_gamma;
    phi_sum *dut_phi;

    std::vector<double> r_real_data;
    std::vector<double> r_imag_data;
    double rho_data;

    std::ofstream gamma_out_file;
    std::ofstream phi_out_file;
    size_t data_length = 0;
    std::string dataset_name = "prog0";

    void clk_gen_process() {
        while (true) {
            clk.write(true);
            wait(5, SC_NS);
            clk.write(false);
            wait(5, SC_NS);
        }
    }

    void reset_gen_process() {
        reset.write(true);
        wait(15, SC_NS);
        reset.write(false);
        wait(SC_ZERO_TIME);
    }

    void load_data() {
         std::string base_path = "DICD/Golden_data/" + dataset_name + "/";
         std::string r_real_path = base_path + "dataset_r_real_bin.txt";
         std::string r_imag_path = base_path + "dataset_r_imag_bin.txt";
         std::string rho_path = base_path + "dataset_rho_bin.txt";

         std::ifstream r_real_file(r_real_path);
         std::ifstream r_imag_file(r_imag_path);
         std::ifstream rho_file(rho_path);
         std::string line;

         std::cout << "INFO: Loading data for dataset '" << dataset_name << "'..." << std::endl;

         if (!r_real_file) { std::cerr << "ERR: Cannot open " << r_real_path << "!" << std::endl; sc_stop(); return; }
         if (!r_imag_file) { std::cerr << "ERR: Cannot open " << r_imag_path << "!" << std::endl; sc_stop(); return; }
         if (!rho_file) { std::cerr << "ERR: Cannot open " << rho_path << "!" << std::endl; sc_stop(); return; }

         int line_num = 0;
         while (std::getline(r_real_file, line)) {
             line_num++;
             line.erase(line.find_last_not_of(" \n\r\t")+1);
             if (!line.empty()) {
                 try { r_real_data.push_back(binToDouble(line, 16, 1, true)); }
                 catch (const std::exception& e) { std::cerr << "ERR: converting r_real line " << line_num << " ('" << line << "') from " << r_real_path << ": " << e.what() << std::endl; sc_stop(); return; }
             }
         }
         r_real_file.close();
         std::cout << "INFO: Loaded " << r_real_data.size() << " real data points." << std::endl;


         line_num = 0;
         while (std::getline(r_imag_file, line)) {
             line_num++;
             line.erase(line.find_last_not_of(" \n\r\t")+1);
              if (!line.empty()) {
                  try { r_imag_data.push_back(binToDouble(line, 16, 1, true)); }
                  catch (const std::exception& e) { std::cerr << "ERR: converting r_imag line " << line_num << " ('" << line << "') from " << r_imag_path << ": " << e.what() << std::endl; sc_stop(); return; }
              }
         }
         r_imag_file.close();
         std::cout << "INFO: Loaded " << r_imag_data.size() << " imag data points." << std::endl;


          if (r_real_data.size() != r_imag_data.size()) { std::cerr << "ERR: r_real (" << r_real_data.size() << ") and r_imag (" << r_imag_data.size() << ") have different lengths for dataset " << dataset_name << "!" << std::endl; sc_stop(); return; }
          data_length = r_real_data.size();
          if (data_length == 0) {
              std::cerr << "ERR: No data loaded from input files for dataset " << dataset_name << "!" << std::endl; sc_stop(); return;
          }

         if (std::getline(rho_file, line) && !line.empty()) {
             line.erase(line.find_last_not_of(" \n\r\t")+1);
             try { rho_data = binToDouble(line, 8, 1, true); p_in_sig.write(rho_data); std::cout << "INFO: Loaded rho = " << rho_data << std::endl; }
             catch (const std::exception& e) { std::cerr << "ERR: converting rho line ('" << line << "') from " << rho_path << ": " << e.what() << std::endl; sc_stop(); return; }
         } else { std::cerr << "ERR: Cannot read rho data from " << rho_path << "!" << std::endl; sc_stop(); return; }
         rho_file.close();
         std::cout << "INFO: Data loading complete." << std::endl;

    }


    void stimulus_process() {

        wait(reset.negedge_event());
        wait(clk.posedge_event());

        size_t data_index = 0;
        while(true) {
             if (data_index < data_length) {
                 r_in_real_sig.write(r_real_data[data_index]);
                 r_in_imag_sig.write(r_imag_data[data_index]);
                 data_index++;
             } else {
                 r_in_real_sig.write(0.0);
                 r_in_imag_sig.write(0.0);
             }
             wait(clk.posedge_event());
        }
    }

    void output_process() {
        std::string gamma_out_filename = "gamma_output_" + dataset_name + ".txt";
        std::string phi_out_filename = "phi_output_" + dataset_name + ".txt";

        gamma_out_file.open(gamma_out_filename);
        phi_out_file.open(phi_out_filename);
        if (!gamma_out_file || !phi_out_file) { std::cerr << "ERR: Cannot open output files!" << std::endl; sc_stop(); return; }
        gamma_out_file << "Time(ns)\tGamma_Real\tGamma_Imag\tValid" << std::endl;
        phi_out_file << "Time(ns)\tPhi\tValid" << std::endl;


        wait(reset.negedge_event());


        while(true) {
            wait(clk.posedge_event());

            sc_time current_time = sc_time_stamp();
            bool gamma_valid = valid_from_gamma_sig.read();
            bool phi_valid = valid_from_phi_sig.read();


            gamma_out_file << current_time.to_double() << "\t"
                           << std::fixed << std::setprecision(10) << gamma_out_real_sig.read() << "\t"
                           << std::fixed << std::setprecision(10) << gamma_out_imag_sig.read() << "\t"
                           << gamma_valid << std::endl;


            phi_out_file << current_time.to_double() << "\t"
                         << std::fixed << std::setprecision(10) << phi_out_sig.read() << "\t"
                         << phi_valid << std::endl;

             if (!gamma_out_file || !phi_out_file) {
                  std::cerr << "ERR: Error during writing to output files at " << sc_time_stamp() << std::endl;
                  sc_stop(); return;
             }
        }
    }

    SC_CTOR(top_testbench) {
        if (sc_argc() > 1) {
            dataset_name = sc_argv()[1];
        } else {
             std::cout << "WARN: No dataset specified via command line, using default: " << dataset_name << std::endl;
             std::cout << "      Usage: ./run_sim_arg <dataset_name>" << std::endl;
        }
        std::cout << "INFO: Testbench configured for dataset: " << dataset_name << std::endl;

        load_data();


        dut_delay = new delay_n("dut_delay");
        dut_gamma = new gamma_sum("dut_gamma");
        dut_phi = new phi_sum("dut_phi");

        dut_delay->clk(clk);
        dut_delay->reset(reset);
        dut_delay->r_in_real(r_in_real_sig);
        dut_delay->r_in_imag(r_in_imag_sig);
        dut_delay->r_out_real(r_out_real_sig);
        dut_delay->r_out_imag(r_out_imag_sig);
        dut_delay->r_delayed_out_real(r_delayed_out_real_sig);
        dut_delay->r_delayed_out_imag(r_delayed_out_imag_sig);
        dut_delay->valid_out(valid_from_delay_sig);

        dut_gamma->clk(clk);
        dut_gamma->reset(reset);
        dut_gamma->r_k_in_real(r_out_real_sig);
        dut_gamma->r_k_in_imag(r_out_imag_sig);
        dut_gamma->r_k_minus_N_in_real(r_delayed_out_real_sig);
        dut_gamma->r_k_minus_N_in_imag(r_delayed_out_imag_sig);
        dut_gamma->valid_in(valid_from_delay_sig);
        dut_gamma->gamma_out_real(gamma_out_real_sig);
        dut_gamma->gamma_out_imag(gamma_out_imag_sig);
        dut_gamma->valid_out(valid_from_gamma_sig);

        dut_phi->clk(clk);
        dut_phi->reset(reset);
        dut_phi->r_k_in_real(r_out_real_sig);
        dut_phi->r_k_in_imag(r_out_imag_sig);
        dut_phi->r_k_minus_N_in_real(r_delayed_out_real_sig);
        dut_phi->r_k_minus_N_in_imag(r_delayed_out_imag_sig);
        dut_phi->valid_in(valid_from_delay_sig);
        dut_phi->p_in(p_in_sig);
        dut_phi->phi_out(phi_out_sig);
        dut_phi->valid_out(valid_from_phi_sig);

        SC_THREAD(clk_gen_process);
        SC_THREAD(reset_gen_process);
        SC_THREAD(stimulus_process);
        SC_THREAD(output_process);

    }

    ~top_testbench() {
        delete dut_delay;
        delete dut_gamma;
        delete dut_phi;
         if (gamma_out_file.is_open()) gamma_out_file.close();
         if (phi_out_file.is_open()) phi_out_file.close();
    }
};

int sc_main(int argc, char* argv[]) {

    std::string dataset_name_main = "prog0";
    if (argc > 1) {
        dataset_name_main = argv[1];
    } else {
        std::cout << "INFO: No dataset specified, using default 'prog0'." << std::endl;
        std::cout << "      Usage: ./run_sim_arg <dataset_name>" << std::endl;
    }
    std::string r_real_path_check = "DICD/Golden_data/" + dataset_name_main + "/dataset_r_real_bin.txt";
    std::cout << "--- Checking Dataset (" << dataset_name_main << ") ---" << std::endl;

    std::ifstream r_real_file_check(r_real_path_check);
    size_t num_lines = 0;
    std::string temp_line;
    if(r_real_file_check) {
        while (std::getline(r_real_file_check, temp_line)) {
             bool contains_digit = false;
             for(char c : temp_line) { if(c == '0' || c == '1') { contains_digit=true; break; } }
             if (contains_digit) num_lines++;
        }
        r_real_file_check.close();
         if (num_lines == 0) {
             std::cerr << "ERR: Dataset file " << r_real_path_check << " appears to be empty or contains no binary data!" << std::endl;
             return 1;
         }
    } else {
        std::cerr << "ERR: Cannot open " << r_real_path_check << " to check simulation length." << std::endl;
        return 1;
    }

    sc_time simulation_time = sc_time(15, SC_NS) + sc_time((num_lines + 256 + 16 + 50) * 10.0, SC_NS) ;
    std::cout << "INFO: Dataset length detected: " << num_lines << ". Calculated simulation time: " << simulation_time << std::endl;


    top_testbench tb("TB");


    std::cout << "--- Starting Simulation ---" << std::endl;
    try {
        // Pass argc and argv to sc_start, which initializes the kernel
        //         // sc_start implicitly calls elaboration
                        sc_start(simulation_time, sc_core::SC_RUN_TO_TIME);
                           } catch (const std::exception& e) {
                                   std::cerr << "ERR: SystemC simulation runtime exception: " << e.what() << std::endl;
                                           return 1;
                                               } catch (...) {
                                                       std::cerr << "ERR: Unknown exception during SystemC simulation!" << std::endl;
                                                               return 1;
                                                                   }
      
      
                                                                       std::cout << "--- Simulation Finished ---" << std::endl;
                                                                           std::cout << "INFO: Output files 'gamma_output_" << dataset_name_main << ".txt' and 'phi_output_" << dataset_name_main << ".txt' potentially generated." << std::endl;
      
      
                                                                               return 0;
                                                                               }
