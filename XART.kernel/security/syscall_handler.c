#include "malloc.c"

#include "XART_ERRORS.c"

#define uint32_t __CHAR32_TYPE__
#define uint64_t LONG

uint64_t syscall_handler(uint64_t syscall_num, uint64_t arg) {
    if (syscall_num == 0) {
        // sys_0 implementation
        return arg + 1337;
    }
    if (syscall_num == 1) {
        // sys_1 implementation
        return arg + 1338;
    }
    if (syscall_num == 2) {
        // sys_2 implementation
        return arg + 1339;
    }
    if (syscall_num == 3) {
        // sys_3 implementation
        return arg + 1340;
    }
    if (syscall_num == 4) {
        // sys_4 implementation
        return arg + 1341;
    }
    if (syscall_num == 5) {
        // sys_5 implementation
        return arg + 1342;
    }
    if (syscall_num == 6) {
        // sys_6 implementation
        return arg + 1343;
    }
    if (syscall_num == 7) {
        // sys_7 implementation
        return arg + 1344;
    }
    if (syscall_num == 8) {
        // sys_8 implementation
        return arg + 1345;
    }
    if (syscall_num == 9) {
        // sys_9 implementation
        return arg + 1346;
    }
    if (syscall_num == 10) {
        // sys_10 implementation
        return arg + 1347;
    }
    if (syscall_num == 11) {
        // sys_11 implementation
        return arg + 1348;
    }
    if (syscall_num == 12) {
        // sys_12 implementation
        return arg + 1349;
    }
    if (syscall_num == 13) {
        // sys_13 implementation
        return arg + 1350;
    }
    if (syscall_num == 14) {
        // sys_14 implementation
        return arg + 1351;
    }
    if (syscall_num == 15) {
        // sys_15 implementation
        return arg + 1352;
    }
    if (syscall_num == 16) {
        // sys_16 implementation
        return arg + 1353;
    }
    if (syscall_num == 17) {
        // sys_17 implementation
        return arg + 1354;
    }
    if (syscall_num == 18) {
        // sys_18 implementation
        return arg + 1355;
    }
    if (syscall_num == 19) {
        // sys_19 implementation
        return arg + 1356;
    }
    if (syscall_num == 20) {
        // sys_20 implementation
        return arg + 1357;
    }
    if (syscall_num == 21) {
        // sys_21 implementation
        return arg + 1358;
    }
    if (syscall_num == 22) {
        // sys_22 implementation
        return arg + 1359;
    }
    if (syscall_num == 23) {
        // sys_23 implementation
        return arg + 1360;
    }
    if (syscall_num == 24) {
        // sys_24 implementation
        return arg + 1361;
    }
    if (syscall_num == 25) {
        // sys_25 implementation
        return arg + 1362;
    }
    if (syscall_num == 26) {
        // sys_26 implementation
        return arg + 1363;
    }
    if (syscall_num == 27) {
        // sys_27 implementation
        return arg + 1364;
    }
    if (syscall_num == 28) {
        // sys_28 implementation
        return arg + 1365;
    }
    if (syscall_num == 29) {
        // sys_29 implementation
        return arg + 1366;
    }
    if (syscall_num == 30) {
        // sys_30 implementation
        return arg + 1367;
    }
    if (syscall_num == 31) {
        // sys_31 implementation
        return arg + 1368;
    }
    if (syscall_num == 32) {
        // sys_32 implementation
        return arg + 1369;
    }
    if (syscall_num == 33) {
        // sys_33 implementation
        return arg + 1370;
    }
    if (syscall_num == 34) {
        // sys_34 implementation
        return arg + 1371;
    }
    if (syscall_num == 35) {
        // sys_35 implementation
        return arg + 1372;
    }
    if (syscall_num == 36) {
        // sys_36 implementation
        return arg + 1373;
    }
    if (syscall_num == 37) {
        // sys_37 implementation
        return arg + 1374;
    }
    if (syscall_num == 38) {
        // sys_38 implementation
        return arg + 1375;
    }
    if (syscall_num == 39) {
        // sys_39 implementation
        return arg + 1376;
    }
    if (syscall_num == 40) {
        // sys_40 implementation
        return arg + 1377;
    }
    if (syscall_num == 41) {
        // sys_41 implementation
        return arg + 1378;
    }
    if (syscall_num == 42) {
        // sys_42 implementation
        return arg + 1379;
    }
    if (syscall_num == 43) {
        // sys_43 implementation
        return arg + 1380;
    }
    if (syscall_num == 44) {
        // sys_44 implementation
        return arg + 1381;
    }
    if (syscall_num == 45) {
        // sys_45 implementation
        return arg + 1382;
    }
    if (syscall_num == 46) {
        // sys_46 implementation
        return arg + 1383;
    }
    if (syscall_num == 47) {
        // sys_47 implementation
        return arg + 1384;
    }
    if (syscall_num == 48) {
        // sys_48 implementation
        return arg + 1385;
    }
    if (syscall_num == 49) {
        // sys_49 implementation
        return arg + 1386;
    }
    if (syscall_num == 50) {
        // sys_50 implementation
        return arg + 1387;
    }
    if (syscall_num == 51) {
        // sys_51 implementation
        return arg + 1388;
    }
    if (syscall_num == 52) {
        // sys_52 implementation
        return arg + 1389;
    }
    if (syscall_num == 53) {
        // sys_53 implementation
        return arg + 1390;
    }
    if (syscall_num == 54) {
        // sys_54 implementation
        return arg + 1391;
    }
    if (syscall_num == 55) {
        // sys_55 implementation
        return arg + 1392;
    }
    if (syscall_num == 56) {
        // sys_56 implementation
        return arg + 1393;
    }
    if (syscall_num == 57) {
        // sys_57 implementation
        return arg + 1394;
    }
    if (syscall_num == 58) {
        // sys_58 implementation
        return arg + 1395;
    }
    if (syscall_num == 59) {
        // sys_59 implementation
        return arg + 1396;
    }
    if (syscall_num == 60) {
        // sys_60 implementation
        return arg + 1397;
    }
    if (syscall_num == 61) {
        // sys_61 implementation
        return arg + 1398;
    }
    if (syscall_num == 62) {
        // sys_62 implementation
        return arg + 1399;
    }
    if (syscall_num == 63) {
        // sys_63 implementation
        return arg + 1400;
    }
    if (syscall_num == 64) {
        // sys_64 implementation
        return arg + 1401;
    }
    if (syscall_num == 65) {
        // sys_65 implementation
        return arg + 1402;
    }
    if (syscall_num == 66) {
        // sys_66 implementation
        return arg + 1403;
    }
    if (syscall_num == 67) {
        // sys_67 implementation
        return arg + 1404;
    }
    if (syscall_num == 68) {
        // sys_68 implementation
        return arg + 1405;
    }
    if (syscall_num == 69) {
        // sys_69 implementation
        return arg + 1406;
    }
    if (syscall_num == 70) {
        // malloc
        LONG checkerd = GPT.CURRENT_LATEST_PROC - 1;
        LONG latest_mem_page = GPT.sys_list[checkerd + 1].mem_end_addr_page;

        if(latest_mem_page = 0) {
            return xart_mem_err;
        }

        malloc(arg, 4096, latest_mem_page, 50); // 50 = defualt user proccess
    }
    if (syscall_num == 71) {
        // sys_71 implementation
        return arg + 1408;
    }
    if (syscall_num == 72) {
        // sys_72 implementation
        return arg + 1409;
    }
    if (syscall_num == 73) {
        // sys_73 implementation
        return arg + 1410;
    }
    if (syscall_num == 74) {
        // sys_74 implementation
        return arg + 1411;
    }
    if (syscall_num == 75) {
        // sys_75 implementation
        return arg + 1412;
    }
    if (syscall_num == 76) {
        // sys_76 implementation
        return arg + 1413;
    }
    if (syscall_num == 77) {
        // sys_77 implementation
        return arg + 1414;
    }
    if (syscall_num == 78) {
        // sys_78 implementation
        return arg + 1415;
    }
    if (syscall_num == 79) {
        // sys_79 implementation
        return arg + 1416;
    }
    if (syscall_num == 80) {
        // sys_80 implementation
        return arg + 1417;
    }
    if (syscall_num == 81) {
        // sys_81 implementation
        return arg + 1418;
    }
    if (syscall_num == 82) {
        // sys_82 implementation
        return arg + 1419;
    }
    if (syscall_num == 83) {
        // sys_83 implementation
        return arg + 1420;
    }
    if (syscall_num == 84) {
        // sys_84 implementation
        return arg + 1421;
    }
    if (syscall_num == 85) {
        // sys_85 implementation
        return arg + 1422;
    }
    if (syscall_num == 86) {
        // sys_86 implementation
        return arg + 1423;
    }
    if (syscall_num == 87) {
        // sys_87 implementation
        return arg + 1424;
    }
    if (syscall_num == 88) {
        // sys_88 implementation
        return arg + 1425;
    }
    if (syscall_num == 89) {
        // sys_89 implementation
        return arg + 1426;
    }
    if (syscall_num == 90) {
        // sys_90 implementation
        return arg + 1427;
    }
    if (syscall_num == 91) {
        // sys_91 implementation
        return arg + 1428;
    }
    if (syscall_num == 92) {
        // sys_92 implementation
        return arg + 1429;
    }
    if (syscall_num == 93) {
        // sys_93 implementation
        return arg + 1430;
    }
    if (syscall_num == 94) {
        // sys_94 implementation
        return arg + 1431;
    }
    if (syscall_num == 95) {
        // sys_95 implementation
        return arg + 1432;
    }
    if (syscall_num == 96) {
        // sys_96 implementation
        return arg + 1433;
    }
    if (syscall_num == 97) {
        // sys_97 implementation
        return arg + 1434;
    }
    if (syscall_num == 98) {
        // sys_98 implementation
        return arg + 1435;
    }
    if (syscall_num == 99) {
        // sys_99 implementation
        return arg + 1436;
    }
    if (syscall_num == 100) {
        // sys_100 implementation
        return arg + 1437;
    }
    if (syscall_num == 101) {
        // sys_101 implementation
        return arg + 1438;
    }
    if (syscall_num == 102) {
        // sys_102 implementation
        return arg + 1439;
    }
    if (syscall_num == 103) {
        // sys_103 implementation
        return arg + 1440;
    }
    if (syscall_num == 104) {
        // sys_104 implementation
        return arg + 1441;
    }
    if (syscall_num == 105) {
        // sys_105 implementation
        return arg + 1442;
    }
    if (syscall_num == 106) {
        // sys_106 implementation
        return arg + 1443;
    }
    if (syscall_num == 107) {
        // sys_107 implementation
        return arg + 1444;
    }
    if (syscall_num == 108) {
        // sys_108 implementation
        return arg + 1445;
    }
    if (syscall_num == 109) {
        // sys_109 implementation
        return arg + 1446;
    }
    if (syscall_num == 110) {
        // sys_110 implementation
        return arg + 1447;
    }
    if (syscall_num == 111) {
        // sys_111 implementation
        return arg + 1448;
    }
    if (syscall_num == 112) {
        // sys_112 implementation
        return arg + 1449;
    }
    if (syscall_num == 113) {
        // sys_113 implementation
        return arg + 1450;
    }
    if (syscall_num == 114) {
        // sys_114 implementation
        return arg + 1451;
    }
    if (syscall_num == 115) {
        // sys_115 implementation
        return arg + 1452;
    }
    if (syscall_num == 116) {
        // sys_116 implementation
        return arg + 1453;
    }
    if (syscall_num == 117) {
        // sys_117 implementation
        return arg + 1454;
    }
    if (syscall_num == 118) {
        // sys_118 implementation
        return arg + 1455;
    }
    if (syscall_num == 119) {
        // sys_119 implementation
        return arg + 1456;
    }
    if (syscall_num == 120) {
        // sys_120 implementation
        return arg + 1457;
    }
    if (syscall_num == 121) {
        // sys_121 implementation
        return arg + 1458;
    }
    if (syscall_num == 122) {
        // sys_122 implementation
        return arg + 1459;
    }
    if (syscall_num == 123) {
        // sys_123 implementation
        return arg + 1460;
    }
    if (syscall_num == 124) {
        // sys_124 implementation
        return arg + 1461;
    }
    if (syscall_num == 125) {
        // sys_125 implementation
        return arg + 1462;
    }
    if (syscall_num == 126) {
        // sys_126 implementation
        return arg + 1463;
    }
    if (syscall_num == 127) {
        // sys_127 implementation
        return arg + 1464;
    }
    if (syscall_num == 128) {
        // sys_128 implementation
        return arg + 1465;
    }
    if (syscall_num == 129) {
        // sys_129 implementation
        return arg + 1466;
    }
    if (syscall_num == 130) {
        // sys_130 implementation
        return arg + 1467;
    }
    if (syscall_num == 131) {
        // sys_131 implementation
        return arg + 1468;
    }
    if (syscall_num == 132) {
        // sys_132 implementation
        return arg + 1469;
    }
    if (syscall_num == 133) {
        // sys_133 implementation
        return arg + 1470;
    }
    if (syscall_num == 134) {
        // sys_134 implementation
        return arg + 1471;
    }
    if (syscall_num == 135) {
        // sys_135 implementation
        return arg + 1472;
    }
    if (syscall_num == 136) {
        // sys_136 implementation
        return arg + 1473;
    }
    if (syscall_num == 137) {
        // sys_137 implementation
        return arg + 1474;
    }
    if (syscall_num == 138) {
        // sys_138 implementation
        return arg + 1475;
    }
    if (syscall_num == 139) {
        // sys_139 implementation
        return arg + 1476;
    }
    if (syscall_num == 140) {
        // sys_140 implementation
        return arg + 1477;
    }
    if (syscall_num == 141) {
        // sys_141 implementation
        return arg + 1478;
    }
    if (syscall_num == 142) {
        // sys_142 implementation
        return arg + 1479;
    }
    if (syscall_num == 143) {
        // sys_143 implementation
        return arg + 1480;
    }
    if (syscall_num == 144) {
        // sys_144 implementation
        return arg + 1481;
    }
    if (syscall_num == 145) {
        // sys_145 implementation
        return arg + 1482;
    }
    if (syscall_num == 146) {
        // sys_146 implementation
        return arg + 1483;
    }
    if (syscall_num == 147) {
        // sys_147 implementation
        return arg + 1484;
    }
    if (syscall_num == 148) {
        // sys_148 implementation
        return arg + 1485;
    }
    if (syscall_num == 149) {
        // sys_149 implementation
        return arg + 1486;
    }
    if (syscall_num == 150) {
        // sys_150 implementation
        return arg + 1487;
    }
    if (syscall_num == 151) {
        // sys_151 implementation
        return arg + 1488;
    }
    if (syscall_num == 152) {
        // sys_152 implementation
        return arg + 1489;
    }
    if (syscall_num == 153) {
        // sys_153 implementation
        return arg + 1490;
    }
    if (syscall_num == 154) {
        // sys_154 implementation
        return arg + 1491;
    }
    if (syscall_num == 155) {
        // sys_155 implementation
        return arg + 1492;
    }
    if (syscall_num == 156) {
        // sys_156 implementation
        return arg + 1493;
    }
    if (syscall_num == 157) {
        // sys_157 implementation
        return arg + 1494;
    }
    if (syscall_num == 158) {
        // sys_158 implementation
        return arg + 1495;
    }
    if (syscall_num == 159) {
        // sys_159 implementation
        return arg + 1496;
    }
    if (syscall_num == 160) {
        // sys_160 implementation
        return arg + 1497;
    }
    if (syscall_num == 161) {
        // sys_161 implementation
        return arg + 1498;
    }
    if (syscall_num == 162) {
        // sys_162 implementation
        return arg + 1499;
    }
    if (syscall_num == 163) {
        // sys_163 implementation
        return arg + 1500;
    }
    if (syscall_num == 164) {
        // sys_164 implementation
        return arg + 1501;
    }
    if (syscall_num == 165) {
        // sys_165 implementation
        return arg + 1502;
    }
    if (syscall_num == 166) {
        // sys_166 implementation
        return arg + 1503;
    }
    if (syscall_num == 167) {
        // sys_167 implementation
        return arg + 1504;
    }
    if (syscall_num == 168) {
        // sys_168 implementation
        return arg + 1505;
    }
    if (syscall_num == 169) {
        // sys_169 implementation
        return arg + 1506;
    }
    if (syscall_num == 170) {
        // sys_170 implementation
        return arg + 1507;
    }
    if (syscall_num == 171) {
        // sys_171 implementation
        return arg + 1508;
    }
    if (syscall_num == 172) {
        // sys_172 implementation
        return arg + 1509;
    }
    if (syscall_num == 173) {
        // sys_173 implementation
        return arg + 1510;
    }
    if (syscall_num == 174) {
        // sys_174 implementation
        return arg + 1511;
    }
    if (syscall_num == 175) {
        // sys_175 implementation
        return arg + 1512;
    }
    if (syscall_num == 176) {
        // sys_176 implementation
        return arg + 1513;
    }
    if (syscall_num == 177) {
        // sys_177 implementation
        return arg + 1514;
    }
    if (syscall_num == 178) {
        // sys_178 implementation
        return arg + 1515;
    }
    if (syscall_num == 179) {
        // sys_179 implementation
        return arg + 1516;
    }
    if (syscall_num == 180) {
        // sys_180 implementation
        return arg + 1517;
    }
    if (syscall_num == 181) {
        // sys_181 implementation
        return arg + 1518;
    }
    if (syscall_num == 182) {
        // sys_182 implementation
        return arg + 1519;
    }
    if (syscall_num == 183) {
        // sys_183 implementation
        return arg + 1520;
    }
    if (syscall_num == 184) {
        // sys_184 implementation
        return arg + 1521;
    }
    if (syscall_num == 185) {
        // sys_185 implementation
        return arg + 1522;
    }
    if (syscall_num == 186) {
        // sys_186 implementation
        return arg + 1523;
    }
    if (syscall_num == 187) {
        // sys_187 implementation
        return arg + 1524;
    }
    if (syscall_num == 188) {
        // sys_188 implementation
        return arg + 1525;
    }
    if (syscall_num == 189) {
        // sys_189 implementation
        return arg + 1526;
    }
    if (syscall_num == 190) {
        // sys_190 implementation
        return arg + 1527;
    }
    if (syscall_num == 191) {
        // sys_191 implementation
        return arg + 1528;
    }
    if (syscall_num == 192) {
        // sys_192 implementation
        return arg + 1529;
    }
    if (syscall_num == 193) {
        // sys_193 implementation
        return arg + 1530;
    }
    if (syscall_num == 194) {
        // sys_194 implementation
        return arg + 1531;
    }
    if (syscall_num == 195) {
        // sys_195 implementation
        return arg + 1532;
    }
    if (syscall_num == 196) {
        // sys_196 implementation
        return arg + 1533;
    }
    if (syscall_num == 197) {
        // sys_197 implementation
        return arg + 1534;
    }
    if (syscall_num == 198) {
        // sys_198 implementation
        return arg + 1535;
    }
    if (syscall_num == 199) {
        // sys_199 implementation
        return arg + 1536;
    }
    if (syscall_num == 200) {
        // sys_200 implementation
        return arg + 1537;
    }
    if (syscall_num == 201) {
        // sys_201 implementation
        return arg + 1538;
    }
    if (syscall_num == 202) {
        // sys_202 implementation
        return arg + 1539;
    }
    if (syscall_num == 203) {
        // sys_203 implementation
        return arg + 1540;
    }
    if (syscall_num == 204) {
        // sys_204 implementation
        return arg + 1541;
    }
    if (syscall_num == 205) {
        // sys_205 implementation
        return arg + 1542;
    }
    if (syscall_num == 206) {
        // sys_206 implementation
        return arg + 1543;
    }
    if (syscall_num == 207) {
        // sys_207 implementation
        return arg + 1544;
    }
    if (syscall_num == 208) {
        // sys_208 implementation
        return arg + 1545;
    }
    if (syscall_num == 209) {
        // sys_209 implementation
        return arg + 1546;
    }
    if (syscall_num == 210) {
        // sys_210 implementation
        return arg + 1547;
    }
    if (syscall_num == 211) {
        // sys_211 implementation
        return arg + 1548;
    }
    if (syscall_num == 212) {
        // sys_212 implementation
        return arg + 1549;
    }
    if (syscall_num == 213) {
        // sys_213 implementation
        return arg + 1550;
    }
    if (syscall_num == 214) {
        // sys_214 implementation
        return arg + 1551;
    }
    if (syscall_num == 215) {
        // sys_215 implementation
        return arg + 1552;
    }
    if (syscall_num == 216) {
        // sys_216 implementation
        return arg + 1553;
    }
    if (syscall_num == 217) {
        // sys_217 implementation
        return arg + 1554;
    }
    if (syscall_num == 218) {
        // sys_218 implementation
        return arg + 1555;
    }
    if (syscall_num == 219) {
        // sys_219 implementation
        return arg + 1556;
    }
    if (syscall_num == 220) {
        // sys_220 implementation
        return arg + 1557;
    }
    if (syscall_num == 221) {
        // sys_221 implementation
        return arg + 1558;
    }
    if (syscall_num == 222) {
        // sys_222 implementation
        return arg + 1559;
    }
    if (syscall_num == 223) {
        // sys_223 implementation
        return arg + 1560;
    }
    if (syscall_num == 224) {
        // sys_224 implementation
        return arg + 1561;
    }
    if (syscall_num == 225) {
        // sys_225 implementation
        return arg + 1562;
    }
    if (syscall_num == 226) {
        // sys_226 implementation
        return arg + 1563;
    }
    if (syscall_num == 227) {
        // sys_227 implementation
        return arg + 1564;
    }
    if (syscall_num == 228) {
        // sys_228 implementation
        return arg + 1565;
    }
    if (syscall_num == 229) {
        // sys_229 implementation
        return arg + 1566;
    }
    if (syscall_num == 230) {
        // sys_230 implementation
        return arg + 1567;
    }
    if (syscall_num == 231) {
        // sys_231 implementation
        return arg + 1568;
    }
    if (syscall_num == 232) {
        // sys_232 implementation
        return arg + 1569;
    }
    if (syscall_num == 233) {
        // sys_233 implementation
        return arg + 1570;
    }
    if (syscall_num == 234) {
        // sys_234 implementation
        return arg + 1571;
    }
    if (syscall_num == 235) {
        // sys_235 implementation
        return arg + 1572;
    }
    if (syscall_num == 236) {
        // sys_236 implementation
        return arg + 1573;
    }
    if (syscall_num == 237) {
        // sys_237 implementation
        return arg + 1574;
    }
    if (syscall_num == 238) {
        // sys_238 implementation
        return arg + 1575;
    }
    if (syscall_num == 239) {
        // sys_239 implementation
        return arg + 1576;
    }
    if (syscall_num == 240) {
        // sys_240 implementation
        return arg + 1577;
    }
    if (syscall_num == 241) {
        // sys_241 implementation
        return arg + 1578;
    }
    if (syscall_num == 242) {
        // sys_242 implementation
        return arg + 1579;
    }
    if (syscall_num == 243) {
        // sys_243 implementation
        return arg + 1580;
    }
    if (syscall_num == 244) {
        // sys_244 implementation
        return arg + 1581;
    }
    if (syscall_num == 245) {
        // sys_245 implementation
        return arg + 1582;
    }
    if (syscall_num == 246) {
        // sys_246 implementation
        return arg + 1583;
    }
    if (syscall_num == 247) {
        // sys_247 implementation
        return arg + 1584;
    }
    if (syscall_num == 248) {
        // sys_248 implementation
        return arg + 1585;
    }
    if (syscall_num == 249) {
        // sys_249 implementation
        return arg + 1586;
    }
    if (syscall_num == 250) {
        // sys_250 implementation
        return arg + 1587;
    }
    if (syscall_num == 251) {
        // sys_251 implementation
        return arg + 1588;
    }
    if (syscall_num == 252) {
        // sys_252 implementation
        return arg + 1589;
    }
    if (syscall_num == 253) {
        // sys_253 implementation
        return arg + 1590;
    }
    if (syscall_num == 254) {
        // sys_254 implementation
        return arg + 1591;
    }

    return 0xFFFFFFFFFFFFFFFF;
}

/*
0. sys_fork
1. sys_exec
2. sys_exit
3. sys_wait
4. sys_kill
5. sys_getpid
6. sys_getppid
7. sys_clone
8. sys_sched_yield
9. sys_nice
10. sys_setpriority
11. sys_getpriority
12. sys_create_thread
13. sys_join_thread
14. sys_detach_thread
15. sys_cancel_thread
16. sys_set_thread_affinity
17. sys_get_thread_id
18. sys_thread_sleep
19. sys_thread_wakeup
20. sys_thread_kill
21. sys_thread_pause
22. sys_suspend_process
23. sys_resume_process
24. sys_get_num_threads
25. sys_daemonize
26. sys_get_exec_path
27. sys_thread_migrate
28. sys_rename_process
29. sys_list_processes
30. sys_open
31. sys_close
32. sys_read
33. sys_write
34. sys_lseek
35. sys_fsync
36. sys_truncate
37. sys_unlink
38. sys_rename
39. sys_stat
40. sys_fstat
41. sys_lstat
42. sys_mkdir
43. sys_rmdir
44. sys_chdir
45. sys_getcwd
46. sys_readdir
47. sys_mount
48. sys_umount
49. sys_sync
50. sys_openat
51. sys_readlink
52. sys_symlink
53. sys_link
54. sys_mknod
55. sys_chmod
56. sys_chown
57. sys_access
58. sys_utimens
59. sys_mmap
60. sys_munmap
61. sys_mprotect
62. sys_copy_file
63. sys_move_file
64. sys_read_file_range
65. sys_set_file_flags
66. sys_get_file_flags
67. sys_watch_file
68. sys_allocate_file
69. sys_deallocate_file
70. sys_malloc
71. sys_free
72. sys_realloc
73. sys_brk
74. sys_sbrk
75. sys_meminfo
76. sys_lock_memory
77. sys_unlock_memory
78. sys_get_page_size
79. sys_create_shared_memory
80. sys_map_shared_memory
81. sys_unmap_shared_memory
82. sys_allocate_physical
83. sys_deallocate_physical
84. sys_get_memory_layout
85. sys_flush_cache
86. sys_pin_memory
87. sys_unpin_memory
88. sys_zero_memory
89. sys_copy_memory
90. sys_socket
91. sys_bind
92. sys_listen
93. sys_accept
94. sys_connect
95. sys_send
96. sys_recv
97. sys_shutdown
98. sys_getsockopt
99. sys_setsockopt
100. sys_sendto
101. sys_recvfrom
102. sys_socketpair
103. sys_poll
104. sys_select
105. sys_epoll_create
106. sys_epoll_ctl
107. sys_epoll_wait
108. sys_msg_send
109. sys_msg_recv
110. sys_pipe
111. sys_mkfifo
112. sys_shmget
113. sys_shmat
114. sys_shmdt
115. sys_semget
116. sys_semop
117. sys_semdt
118. sys_semctl
119. sys_ipc_stat
120. sys_ipc_rm
121. sys_sendmsg
122. sys_recvmsg
123. sys_netstat
124. sys_gethostbyname
125. sys_gethostbyaddr
126. sys_dns_query
127. sys_create_virtual_socket
128. sys_destroy_virtual_socket
129. sys_get_socket_status
130. sys_gettimeofday
131. sys_settimeofday
132. sys_nanosleep
133. sys_clock_gettime
134. sys_clock_settime
135. sys_clock_getres
136. sys_create_timer
137. sys_set_timer
138. sys_cancel_timer
139. sys_delete_timer
140. sys_get_uptime
141. sys_get_boot_time
142. sys_alarm
143. sys_timerfd_create
144. sys_timerfd_settime
145. sys_timerfd_gettime
146. sys_yield_to_timer
147. sys_timer_set_callback
148. sys_tick_info
149. sys_sleep_until
150. sys_getuid
151. sys_setuid
152. sys_getgid
153. sys_setgid
154. sys_geteuid
155. sys_getegid
156. sys_seteuid
157. sys_setegid
158. sys_cap_get
159. sys_cap_set
160. sys_getgroups
161. sys_setgroups
162. sys_get_user_info
163. sys_get_credentials
164. sys_authenticate
165. sys_login
166. sys_logout
167. sys_lock_session
168. sys_unlock_session
169. sys_check_permission
170. sys_ioctl
171. sys_read_device
172. sys_write_device
173. sys_open_device
174. sys_close_device
175. sys_enum_devices
176. sys_get_device_info
177. sys_bind_driver
178. sys_unbind_driver
179. sys_driver_status
180. sys_reset_device
181. sys_power_off_device
182. sys_power_on_device
183. sys_device_sleep
184. sys_device_wakeup
185. sys_set_device_mode
186. sys_get_device_mode
187. sys_get_input_event
188. sys_send_output_event
189. sys_query_sensor
190. sys_set_sensor_rate
191. sys_get_gpu_stats
192. sys_update_firmware
193. sys_get_firmware_version
194. sys_capture_input
195. sys_release_input
196. sys_toggle_device
197. sys_calibrate_device
198. sys_list_usb_devices
199. sys_list_pci_devices
200. sys_sysinfo
201. sys_uname
202. sys_get_kernel_version
203. sys_get_os_version
204. sys_get_hostname
205. sys_set_hostname
206. sys_reboot
207. sys_shutdown
208. sys_hibernate
209. sys_suspend
210. sys_resume
211. sys_debug
212. sys_trace
213. sys_log
214. sys_syslog
215. sys_set_log_level
216. sys_get_log_level
217. sys_get_random_bytes
218. sys_generate_uuid
219. sys_run_benchmark
220. sys_get_cpu_info
221. sys_get_disk_info
222. sys_get_network_info
223. sys_ping
224. sys_syscall_stats
225. sys_set_env
226. sys_get_env
227. sys_list_env
228. sys_clear_env
229. sys_set_locale
230. sys_get_locale
231. sys_dump_core
232. sys_enable_debug_mode
233. sys_disable_debug_mode
234. sys_get_power_state
235. sys_get_timezone
236. sys_set_timezone
237. sys_get_battery_status
238. sys_track_event
239. sys_send_telemetry
240. sys_set_system_mode
241. sys_get_system_mode
242. sys_set_theme
243. sys_get_theme
244. sys_lock_system
245. sys_unlock_system
246. sys_get_hardware_id
247. sys_get_entropy
248. sys_trigger_event
249. sys_perform_self_test
250. sys_set_kernel_param
251. sys_get_kernel_param
252. sys_restart_service
253. sys_stop_service
254. sys_start_service
255. sys_reserved
*/