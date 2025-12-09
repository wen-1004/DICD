wvSetPosition -win $_nWave1 {("G1" 0)}
wvOpenFile -win $_nWave1 {/home/patata0717/DICD/HW3_groupx/build/top.fsdb}
verdiSetActWin -win $_nWave1
wvGetSignalOpen -win $_nWave1
wvGetSignalSetScope -win $_nWave1 "/tb_top"
wvGetSignalSetScope -win $_nWave1 "/tb_top/dut"
wvExit
