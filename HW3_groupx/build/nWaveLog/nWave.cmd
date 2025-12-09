wvSetPosition -win $_nWave1 {("G1" 0)}
wvOpenFile -win $_nWave1 {/home/patata0717/DICD/HW3_groupx/build/top.fsdb}
wvResizeWindow -win $_nWave1 0 23 1280 649
verdiSetActWin -win $_nWave1
wvGetSignalOpen -win $_nWave1
wvGetSignalSetScope -win $_nWave1 "/tb_top"
wvGetSignalSetScope -win $_nWave1 "/tb_top/dut"
wvSetPosition -win $_nWave1 {("G1" 5)}
wvSetPosition -win $_nWave1 {("G1" 5)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/rst} \
{/tb_top/dut/theta\[7:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 1 2 3 4 5 )} 
wvSetPosition -win $_nWave1 {("G1" 5)}
wvSetPosition -win $_nWave1 {("G1" 5)}
wvSetPosition -win $_nWave1 {("G1" 5)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/rst} \
{/tb_top/dut/theta\[7:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 1 2 3 4 5 )} 
wvSetPosition -win $_nWave1 {("G1" 5)}
wvGetSignalClose -win $_nWave1
wvGetSignalOpen -win $_nWave1
wvGetSignalSetScope -win $_nWave1 "/tb_top"
wvGetSignalSetScope -win $_nWave1 "/tb_top/dut"
wvSetPosition -win $_nWave1 {("G1" 7)}
wvSetPosition -win $_nWave1 {("G1" 7)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/rst} \
{/tb_top/dut/theta\[7:0\]} \
{/tb_top/dut/rx_img_in\[15:0\]} \
{/tb_top/dut/rx_re_in\[15:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 6 7 )} 
wvSetPosition -win $_nWave1 {("G1" 7)}
wvSetPosition -win $_nWave1 {("G1" 7)}
wvSetPosition -win $_nWave1 {("G1" 7)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/rst} \
{/tb_top/dut/theta\[7:0\]} \
{/tb_top/dut/rx_img_in\[15:0\]} \
{/tb_top/dut/rx_re_in\[15:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 6 7 )} 
wvSetPosition -win $_nWave1 {("G1" 7)}
wvGetSignalClose -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvSelectSignal -win $_nWave1 {( "G1" 5 6 7 )} 
wvSelectSignal -win $_nWave1 {( "G1" 5 6 7 )} 
wvSetRadix -win $_nWave1 -format UDec
wvSelectSignal -win $_nWave1 {( "G1" 6 )} 
wvSelectSignal -win $_nWave1 {( "G1" 6 )} 
wvSelectSignal -win $_nWave1 {( "G1" 7 )} 
wvSelectSignal -win $_nWave1 {( "G1" 6 7 )} 
wvSelectSignal -win $_nWave1 {( "G1" 5 )} 
wvSelectSignal -win $_nWave1 {( "G1" 4 )} 
wvSetPosition -win $_nWave1 {("G1" 1)}
wvMoveSelected -win $_nWave1
wvSetPosition -win $_nWave1 {("G1" 1)}
wvSetPosition -win $_nWave1 {("G1" 2)}
wvZoomIn -win $_nWave1
wvGetSignalOpen -win $_nWave1
wvGetSignalSetScope -win $_nWave1 "/tb_top"
wvGetSignalSetScope -win $_nWave1 "/tb_top/dut"
wvGetSignalSetScope -win $_nWave1 "/tb_top/dut"
wvSetPosition -win $_nWave1 {("G1" 3)}
wvSetPosition -win $_nWave1 {("G1" 3)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/rst} \
{/tb_top/dut/U_ARGMAX/count\[9:0\]} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/theta\[7:0\]} \
{/tb_top/dut/rx_img_in\[15:0\]} \
{/tb_top/dut/rx_re_in\[15:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 3 )} 
wvSetPosition -win $_nWave1 {("G1" 3)}
wvSetPosition -win $_nWave1 {("G1" 3)}
wvSetPosition -win $_nWave1 {("G1" 3)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/rst} \
{/tb_top/dut/U_ARGMAX/count\[9:0\]} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/theta\[7:0\]} \
{/tb_top/dut/rx_img_in\[15:0\]} \
{/tb_top/dut/rx_re_in\[15:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 3 )} 
wvSetPosition -win $_nWave1 {("G1" 3)}
wvGetSignalClose -win $_nWave1
wvSetPosition -win $_nWave1 {("G1" 7)}
wvSetPosition -win $_nWave1 {("G1" 8)}
wvMoveSelected -win $_nWave1
wvSetPosition -win $_nWave1 {("G1" 8)}
wvSelectSignal -win $_nWave1 {( "G1" 8 )} 
wvSetRadix -win $_nWave1 -format UDec
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvSetRadix -win $_nWave1 -2Com
wvSelectSignal -win $_nWave1 {( "G1" 5 )} 
wvSetPosition -win $_nWave1 {("G1" 7)}
wvMoveSelected -win $_nWave1
wvSetPosition -win $_nWave1 {("G1" 7)}
wvDisplayGridCount -win $_nWave1 -off
wvCloseGetStreamsDialog -win $_nWave1
wvAttrOrderConfigDlg -win $_nWave1 -close
wvCloseDetailsViewDlg -win $_nWave1
wvCloseDetailsViewDlg -win $_nWave1 -streamLevel
wvCloseFilterColorizeDlg -win $_nWave1
wvGetSignalClose -win $_nWave1
wvReloadFile -win $_nWave1
wvDisplayGridCount -win $_nWave1 -off
wvCloseGetStreamsDialog -win $_nWave1
wvAttrOrderConfigDlg -win $_nWave1 -close
wvCloseDetailsViewDlg -win $_nWave1
wvCloseDetailsViewDlg -win $_nWave1 -streamLevel
wvCloseFilterColorizeDlg -win $_nWave1
wvGetSignalClose -win $_nWave1
wvReloadFile -win $_nWave1
wvDisplayGridCount -win $_nWave1 -off
wvCloseGetStreamsDialog -win $_nWave1
wvAttrOrderConfigDlg -win $_nWave1 -close
wvCloseDetailsViewDlg -win $_nWave1
wvCloseDetailsViewDlg -win $_nWave1 -streamLevel
wvCloseFilterColorizeDlg -win $_nWave1
wvGetSignalClose -win $_nWave1
wvReloadFile -win $_nWave1
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvScrollDown -win $_nWave1 0
wvZoomOut -win $_nWave1
wvZoomOut -win $_nWave1
wvZoomIn -win $_nWave1
wvZoomIn -win $_nWave1
wvDisplayGridCount -win $_nWave1 -off
wvCloseGetStreamsDialog -win $_nWave1
wvAttrOrderConfigDlg -win $_nWave1 -close
wvCloseDetailsViewDlg -win $_nWave1
wvCloseDetailsViewDlg -win $_nWave1 -streamLevel
wvCloseFilterColorizeDlg -win $_nWave1
wvGetSignalClose -win $_nWave1
wvReloadFile -win $_nWave1
wvSelectSignal -win $_nWave1 {( "G1" 8 )} 
wvSetSearchMode -win $_nWave1 -value "0" -case off -skipGlitch off -X2Y off
wvSelectSignal -win $_nWave1 {( "G1" 8 )} 
wvSearchNext -win $_nWave1
wvSearchPrev -win $_nWave1
wvSearchPrev -win $_nWave1
wvSearchNext -win $_nWave1
wvDisplayGridCount -win $_nWave1 -off
wvCloseGetStreamsDialog -win $_nWave1
wvAttrOrderConfigDlg -win $_nWave1 -close
wvCloseDetailsViewDlg -win $_nWave1
wvCloseDetailsViewDlg -win $_nWave1 -streamLevel
wvCloseFilterColorizeDlg -win $_nWave1
wvGetSignalClose -win $_nWave1
wvReloadFile -win $_nWave1
wvGetSignalOpen -win $_nWave1
wvSetPosition -win $_nWave1 {("G1" 8)}
wvSetPosition -win $_nWave1 {("G1" 8)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/rst} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/rx_img_in\[15:0\]} \
{/tb_top/dut/rx_re_in\[15:0\]} \
{/tb_top/dut/theta\[7:0\]} \
{/tb_top/dut/isPassBarrier} \
{/tb_top/dut/U_ARGMAX/count\[9:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 8 )} 
wvSetPosition -win $_nWave1 {("G1" 8)}
wvSetPosition -win $_nWave1 {("G1" 8)}
wvSetPosition -win $_nWave1 {("G1" 8)}
wvAddSignal -win $_nWave1 -clear
wvAddSignal -win $_nWave1 -group {"G1" \
{/tb_top/dut/clk} \
{/tb_top/dut/rst} \
{/tb_top/dut/in_valid} \
{/tb_top/dut/out_valid} \
{/tb_top/dut/rx_img_in\[15:0\]} \
{/tb_top/dut/rx_re_in\[15:0\]} \
{/tb_top/dut/theta\[7:0\]} \
{/tb_top/dut/isPassBarrier} \
{/tb_top/dut/U_ARGMAX/count\[9:0\]} \
}
wvAddSignal -win $_nWave1 -group {"G2" \
}
wvSelectSignal -win $_nWave1 {( "G1" 8 )} 
wvSetPosition -win $_nWave1 {("G1" 8)}
wvGetSignalClose -win $_nWave1
