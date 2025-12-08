package data_type;

    // -------------------------
    // Width / integer-bit model
    // sc_fixed<W, I>  => FRAC = W - I
    // sc_ufixed<W, I> => FRAC = W - I
    // -------------------------

    // I/O
    localparam int R_W      = 7;
    localparam int R_I      = 1;
    localparam int R_FRAC   = R_W - R_I;      // 6
    typedef logic signed [R_W-1:0] r_t;

    localparam int RHO_W    = 8;
    localparam int RHO_I    = 1;
    localparam int RHO_FRAC = RHO_W - RHO_I;  // 7
    typedef logic signed [RHO_W-1:0] rho_t;

    localparam int EPS_W    = 21;
    localparam int EPS_I    = 1;
    localparam int EPS_FRAC = EPS_W - EPS_I;  // 20
    typedef logic signed [EPS_W-1:0] eps_t;

    typedef logic [7:0] theta_t;

    // Port
    localparam int PHI_W    = 14;
    localparam int PHI_I    = 6;
    localparam int PHI_FRAC = PHI_W - PHI_I;  // 8
    typedef logic signed [PHI_W-1:0] phi_t;

    localparam int GAMMA_W    = 14;
    localparam int GAMMA_I    = 6;
    localparam int GAMMA_FRAC = GAMMA_W - GAMMA_I; // 8
    typedef logic signed [GAMMA_W-1:0] gamma_t;

    localparam int MAG_W    = 14;
    localparam int MAG_I    = 6;
    localparam int MAG_FRAC = MAG_W - MAG_I;  // 8
    typedef logic signed [MAG_W-1:0] mag_t;

    localparam int ANG_W    = 11;
    localparam int ANG_I    = 3;
    localparam int ANG_FRAC = ANG_W - ANG_I;  // 8
    typedef logic signed [ANG_W-1:0] ang_t;

    localparam int LAMBDA_W    = 14;
    localparam int LAMBDA_I    = 6;
    localparam int LAMBDA_FRAC = LAMBDA_W - LAMBDA_I; // 8
    typedef logic signed [LAMBDA_W-1:0] lambda_t;

    // Internal
    localparam int AMBM_W    = 10;
    localparam int AMBM_I    = 2;
    localparam int AMBM_FRAC = AMBM_W - AMBM_I; // 8
    typedef logic signed [AMBM_W-1:0] ambm_t;

    localparam int PI_W    = 8;
    localparam int PI_I    = 0;
    localparam int PI_FRAC = PI_W - PI_I; // 8
    typedef logic [PI_W-1:0] PI_t;

    localparam int RATIO_W    = 8;
    localparam int RATIO_I    = 0;
    localparam int RATIO_FRAC = RATIO_W - RATIO_I; // 8
    typedef logic [RATIO_W-1:0] ratio_t;

endpackage
