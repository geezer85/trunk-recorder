#ifndef INCLUDED_IMBE_FRAME_H
#define INCLUDED_IMBE_FRAME_H

#include "op25_yank.h"
#include "op25_golay.h"
#include "op25_hamming.h"

#include <cstddef>
#include <stdint.h>
#include <vector>

typedef std::vector<bool> voice_codeword;
typedef std::vector<uint8_t> packed_codeword;
typedef const std::vector<bool> const_bit_vector;
typedef std::vector<bool> bit_vector;

static const uint16_t hdu_codeword_bits[658] = {   // 329 symbols = 324 + 5 pad
 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 
 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 144, 145, 146, 147, 
 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 
 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 
 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 
 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 
 212, 213, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 
 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 
 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 
 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 
 278, 279, 280, 281, 282, 283, 284, 285, 288, 289, 290, 291, 292, 293, 294, 295, 
 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 
 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 
 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 
 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 360, 361, 
 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 
 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 
 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 
 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 
 426, 427, 428, 429, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 
 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 
 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 
 476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 
 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 504, 505, 506, 507, 508, 509, 
 510, 511, 512, 513, 514, 515, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 
 526, 527, 528, 529, 530, 531, 532, 533, 534, 535, 536, 537, 538, 539, 540, 541, 
 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557, 
 558, 559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 573, 
 576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 
 592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 603, 604, 605, 606, 607, 
 608, 609, 610, 611, 612, 613, 614, 615, 616, 617, 618, 619, 620, 621, 622, 623, 
 624, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 
 640, 641, 642, 643, 644, 645, 648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 
 658, 659, 660, 661, 662, 663, 664, 665, 666, 667, 668, 669, 670, 671, 672, 673, 
 674, 675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 686, 687, 688, 689, 
 690, 691, 692, 693, 694, 695, 696, 697, 698, 699, 700, 701, 702, 703, 704, 705, 
 706, 707, 708, 709, 710, 711, 712, 713, 714, 715, 716, 717, 720, 721, 722, 723, 
 724, 725, 726, 727, 728, 729, 730, 731, 732, 733, 734, 735, 736, 737, 738, 739, 
 740, 741, 742, 743, 744, 745, 746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 
 756, 757, 758, 759, 760, 761, 762, 763, 764, 765, 766, 767, 768, 769, 770, 771, 
 772, 773, 774, 775, 776, 777, 778, 779, 780, 781, 782, 783, 784, 785, 786, 787, 
 788, 789 };

static const size_t nof_voice_codewords = 9, voice_codeword_sz = 144;

static const uint16_t imbe_ldu_NID_bits[] = {
   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
   86,   87,   88,   89,   90,   91,   92,   93,   94,   95,   96,   97,
   98,   99,  100,  101,  102,  103,  104,  105,  106,  107,  108,  109,
  110,  111,  112,  113 };

static const uint16_t imbe_ldu_status_bits[] = {
   70,   71,  142,  143,  214,  215,  286,  287,  358,  359,  430,  431,
  502,  503,  574,  575,  646,  647,  718,  719,  790,  791,  862,  863,
  934,  935, 1006, 1007, 1078, 1079, 1150, 1151, 1222, 1223, 1294, 1295,
 1366, 1367, 1438, 1439, 1510, 1511, 1582, 1583, 1654, 1655, 1726, 1727 };

static const uint16_t imbe_ldu_lcf_bits[] = {
 410, 411, 412, 413, 414, 415, 420, 421,
 422, 423, 424, 425, 432, 433, 434, 435,
 436, 437, 442, 443, 444, 445, 446, 447,
 600, 601, 602, 603, 604, 605, 610, 611,
 612, 613, 614, 615, 620, 621, 622, 623,
 624, 625, 630, 631, 632, 633, 634, 635,
 788, 789, 792, 793, 794, 795, 800, 801,
 802, 803, 804, 805, 810, 811, 812, 813,
 814, 815, 820, 821, 822, 823, 824, 825 };

// FIXME: separate these into their respective fields
static const uint16_t imbe_ldu_ls_data_bits[] = {
  410,  411,  412,  413,  414,  415,  416,  417,  418,  419,  420,  421,
  422,  423,  424,  425,  426,  427,  428,  429,  432,  433,  434,  435,
  436,  437,  438,  439,  440,  441,  442,  443,  444,  445,  446,  447,
  448,  449,  450,  451,  600,  601,  602,  603,  604,  605,  606,  607,
  608,  609,  610,  611,  612,  613,  614,  615,  616,  617,  618,  619,
  620,  621,  622,  623,  624,  625,  626,  627,  628,  629,  630,  631,
  632,  633,  634,  635,  636,  637,  638,  639,  788,  789,  792,  793,
  794,  795,  796,  797,  798,  799,  800,  801,  802,  803,  804,  805,
  806,  807,  808,  809,  810,  811,  812,  813,  814,  815,  816,  817,
  818,  819,  820,  821,  822,  823,  824,  825,  826,  827,  828,  829,
  978,  979,  980,  981,  982,  983,  984,  985,  986,  987,  988,  989,
  990,  991,  992,  993,  994,  995,  996,  997,  998,  999, 1000, 1001,
 1002, 1003, 1004, 1005, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015,
 1016, 1017, 1018, 1019, 1168, 1169, 1170, 1171, 1172, 1173, 1174, 1175,
 1176, 1177, 1178, 1179, 1180, 1181, 1182, 1183, 1184, 1185, 1186, 1187,
 1188, 1189, 1190, 1191, 1192, 1193, 1194, 1195, 1196, 1197, 1198, 1199,
 1200, 1201, 1202, 1203, 1204, 1205, 1206, 1207, 1356, 1357, 1358, 1359,
 1360, 1361, 1362, 1363, 1364, 1365, 1368, 1369, 1370, 1371, 1372, 1373,
 1374, 1375, 1376, 1377, 1378, 1379, 1380, 1381, 1382, 1383, 1384, 1385,
 1386, 1387, 1388, 1389, 1390, 1391, 1392, 1393, 1394, 1395, 1396, 1397,
 1546, 1547, 1548, 1549, 1550, 1551, 1552, 1553, 1554, 1555, 1556, 1557,
 1558, 1559, 1560, 1561, 1562, 1563, 1564, 1565, 1566, 1567, 1568, 1569,
 1570, 1571, 1572, 1573, 1574, 1575, 1576, 1577 };

static const uint16_t voice_codeword_bits[nof_voice_codewords][voice_codeword_sz] = {

      { 114, 121, 126, 133, 138, 147, 152, 159, 164, 171, 176, 183,
        188, 195, 200, 207, 212, 221, 226, 233, 238, 245, 250, 257,
        115, 120, 127, 132, 139, 146, 153, 158, 165, 170, 177, 182,
        189, 194, 201, 206, 213, 220, 227, 232, 239, 244, 251, 256,
        116, 123, 128, 135, 140, 149, 154, 161, 166, 173, 178, 185,
        190, 197, 202, 209, 216, 223, 228, 235, 240, 247, 252, 259,
        117, 122, 129, 134, 141, 148, 155, 160, 167, 172, 179, 184,
        191, 196, 203, 208, 217, 222, 229, 234, 241, 246, 253, 258,
        118, 125, 130, 137, 144, 151, 156, 163, 168, 175, 180, 187,
        192, 199, 204, 211, 218, 225, 230, 237, 242, 249, 254, 261,
        119, 124, 131, 136, 145, 150, 157, 162, 169, 174, 181, 186,
        193, 198, 205, 210, 219, 224, 231, 236, 243, 248, 255, 260 },

      { 262, 269, 274, 281, 288, 295, 300, 307, 312, 319, 324, 331,
        336, 343, 348, 355, 362, 369, 374, 381, 386, 393, 398, 405,
        263, 268, 275, 280, 289, 294, 301, 306, 313, 318, 325, 330,
        337, 342, 349, 354, 363, 368, 375, 380, 387, 392, 399, 404,
        264, 271, 276, 283, 290, 297, 302, 309, 314, 321, 326, 333,
        338, 345, 350, 357, 364, 371, 376, 383, 388, 395, 400, 407,
        265, 270, 277, 282, 291, 296, 303, 308, 315, 320, 327, 332,
        339, 344, 351, 356, 365, 370, 377, 382, 389, 394, 401, 406,
        266, 273, 278, 285, 292, 299, 304, 311, 316, 323, 328, 335,
        340, 347, 352, 361, 366, 373, 378, 385, 390, 397, 402, 409,
        267, 272, 279, 284, 293, 298, 305, 310, 317, 322, 329, 334,
        341, 346, 353, 360, 367, 372, 379, 384, 391, 396, 403, 408 },

      { 452, 459, 464, 471, 476, 483, 488, 495, 500, 509, 514, 521,
        526, 533, 538, 545, 550, 557, 562, 569, 576, 583, 588, 595,
        453, 458, 465, 470, 477, 482, 489, 494, 501, 508, 515, 520,
        527, 532, 539, 544, 551, 556, 563, 568, 577, 582, 589, 594,
        454, 461, 466, 473, 478, 485, 490, 497, 504, 511, 516, 523,
        528, 535, 540, 547, 552, 559, 564, 571, 578, 585, 590, 597,
        455, 460, 467, 472, 479, 484, 491, 496, 505, 510, 517, 522,
        529, 534, 541, 546, 553, 558, 565, 570, 579, 584, 591, 596,
        456, 463, 468, 475, 480, 487, 492, 499, 506, 513, 518, 525,
        530, 537, 542, 549, 554, 561, 566, 573, 580, 587, 592, 599,
        457, 462, 469, 474, 481, 486, 493, 498, 507, 512, 519, 524,
        531, 536, 543, 548, 555, 560, 567, 572, 581, 586, 593, 598 },

      { 640, 649, 654, 661, 666, 673, 678, 685, 690, 697, 702, 709,
        714, 723, 728, 735, 740, 747, 752, 759, 764, 771, 776, 783,
        641, 648, 655, 660, 667, 672, 679, 684, 691, 696, 703, 708,
        715, 722, 729, 734, 741, 746, 753, 758, 765, 770, 777, 782,
        642, 651, 656, 663, 668, 675, 680, 687, 692, 699, 704, 711,
        716, 725, 730, 737, 742, 749, 754, 761, 766, 773, 778, 785,
        643, 650, 657, 662, 669, 674, 681, 686, 693, 698, 705, 710,
        717, 724, 731, 736, 743, 748, 755, 760, 767, 772, 779, 784,
        644, 653, 658, 665, 670, 677, 682, 689, 694, 701, 706, 713,
        720, 727, 732, 739, 744, 751, 756, 763, 768, 775, 780, 787,
        645, 652, 659, 664, 671, 676, 683, 688, 695, 700, 707, 712,
        721, 726, 733, 738, 745, 750, 757, 762, 769, 774, 781, 786 },

      { 830, 837, 842, 849, 854, 861, 868, 875, 880, 887, 892, 899,
        904, 911, 916, 923, 928, 937, 942, 949, 954, 961, 966, 973,
        831, 836, 843, 848, 855, 860, 869, 874, 881, 886, 893, 898,
        905, 910, 917, 922, 929, 936, 943, 948, 955, 960, 967, 972,
        832, 839, 844, 851, 856, 865, 870, 877, 882, 889, 894, 901,
        906, 913, 918, 925, 930, 939, 944, 951, 956, 963, 968, 975,
        833, 838, 845, 850, 857, 864, 871, 876, 883, 888, 895, 900,
        907, 912, 919, 924, 931, 938, 945, 950, 957, 962, 969, 974,
        834, 841, 846, 853, 858, 867, 872, 879, 884, 891, 896, 903,
        908, 915, 920, 927, 932, 941, 946, 953, 958, 965, 970, 977,
        835, 840, 847, 852, 859, 866, 873, 878, 885, 890, 897, 902,
        909, 914, 921, 926, 933, 940, 947, 952, 959, 964, 971, 976 },

      { 1020, 1027, 1032, 1039, 1044, 1051, 1056, 1063, 1068, 1075, 1082, 1089,
        1094, 1101, 1106, 1113, 1118, 1125, 1130, 1137, 1142, 1149, 1156, 1163,
        1021, 1026, 1033, 1038, 1045, 1050, 1057, 1062, 1069, 1074, 1083, 1088,
        1095, 1100, 1107, 1112, 1119, 1124, 1131, 1136, 1143, 1148, 1157, 1162,
        1022, 1029, 1034, 1041, 1046, 1053, 1058, 1065, 1070, 1077, 1084, 1091,
        1096, 1103, 1108, 1115, 1120, 1127, 1132, 1139, 1144, 1153, 1158, 1165,
        1023, 1028, 1035, 1040, 1047, 1052, 1059, 1064, 1071, 1076, 1085, 1090,
        1097, 1102, 1109, 1114, 1121, 1126, 1133, 1138, 1145, 1152, 1159, 1164,
        1024, 1031, 1036, 1043, 1048, 1055, 1060, 1067, 1072, 1081, 1086, 1093,
        1098, 1105, 1110, 1117, 1122, 1129, 1134, 1141, 1146, 1155, 1160, 1167,
        1025, 1030, 1037, 1042, 1049, 1054, 1061, 1066, 1073, 1080, 1087, 1092,
        1099, 1104, 1111, 1116, 1123, 1128, 1135, 1140, 1147, 1154, 1161, 1166 },

      { 1208, 1215, 1220, 1229, 1234, 1241, 1246, 1253, 1258, 1265, 1270, 1277,
        1282, 1289, 1296, 1303, 1308, 1315, 1320, 1327, 1332, 1339, 1344, 1351,
        1209, 1214, 1221, 1228, 1235, 1240, 1247, 1252, 1259, 1264, 1271, 1276,
        1283, 1288, 1297, 1302, 1309, 1314, 1321, 1326, 1333, 1338, 1345, 1350,
        1210, 1217, 1224, 1231, 1236, 1243, 1248, 1255, 1260, 1267, 1272, 1279,
        1284, 1291, 1298, 1305, 1310, 1317, 1322, 1329, 1334, 1341, 1346, 1353,
        1211, 1216, 1225, 1230, 1237, 1242, 1249, 1254, 1261, 1266, 1273, 1278,
        1285, 1290, 1299, 1304, 1311, 1316, 1323, 1328, 1335, 1340, 1347, 1352,
        1212, 1219, 1226, 1233, 1238, 1245, 1250, 1257, 1262, 1269, 1274, 1281,
        1286, 1293, 1300, 1307, 1312, 1319, 1324, 1331, 1336, 1343, 1348, 1355,
        1213, 1218, 1227, 1232, 1239, 1244, 1251, 1256, 1263, 1268, 1275, 1280,
        1287, 1292, 1301, 1306, 1313, 1318, 1325, 1330, 1337, 1342, 1349, 1354 },

      { 1398, 1405, 1410, 1417, 1422, 1429, 1434, 1443, 1448, 1455, 1460, 1467,
        1472, 1479, 1484, 1491, 1496, 1503, 1508, 1517, 1522, 1529, 1534, 1541,
        1399, 1404, 1411, 1416, 1423, 1428, 1435, 1442, 1449, 1454, 1461, 1466,
        1473, 1478, 1485, 1490, 1497, 1502, 1509, 1516, 1523, 1528, 1535, 1540,
        1400, 1407, 1412, 1419, 1424, 1431, 1436, 1445, 1450, 1457, 1462, 1469,
        1474, 1481, 1486, 1493, 1498, 1505, 1512, 1519, 1524, 1531, 1536, 1543,
        1401, 1406, 1413, 1418, 1425, 1430, 1437, 1444, 1451, 1456, 1463, 1468,
        1475, 1480, 1487, 1492, 1499, 1504, 1513, 1518, 1525, 1530, 1537, 1542,
        1402, 1409, 1414, 1421, 1426, 1433, 1440, 1447, 1452, 1459, 1464, 1471,
        1476, 1483, 1488, 1495, 1500, 1507, 1514, 1521, 1526, 1533, 1538, 1545,
        1403, 1408, 1415, 1420, 1427, 1432, 1441, 1446, 1453, 1458, 1465, 1470,
        1477, 1482, 1489, 1494, 1501, 1506, 1515, 1520, 1527, 1532, 1539, 1544 },
      
      { 1578, 1587, 1592, 1599, 1604, 1611, 1616, 1623, 1628, 1635, 1640, 1647,
        1652, 1661, 1666, 1673, 1678, 1685, 1690, 1697, 1702, 1709, 1714, 1721,
        1579, 1586, 1593, 1598, 1605, 1610, 1617, 1622, 1629, 1634, 1641, 1646,
        1653, 1660, 1667, 1672, 1679, 1684, 1691, 1696, 1703, 1708, 1715, 1720,
        1580, 1589, 1594, 1601, 1606, 1613, 1618, 1625, 1630, 1637, 1642, 1649,
        1656, 1663, 1668, 1675, 1680, 1687, 1692, 1699, 1704, 1711, 1716, 1723,
        1581, 1588, 1595, 1600, 1607, 1612, 1619, 1624, 1631, 1636, 1643, 1648,
        1657, 1662, 1669, 1674, 1681, 1686, 1693, 1698, 1705, 1710, 1717, 1722,
        1584, 1591, 1596, 1603, 1608, 1615, 1620, 1627, 1632, 1639, 1644, 1651,
        1658, 1665, 1670, 1677, 1682, 1689, 1694, 1701, 1706, 1713, 1718, 1725,
        1585, 1590, 1597, 1602, 1609, 1614, 1621, 1626, 1633, 1638, 1645, 1650,
        1659, 1664, 1671, 1676, 1683, 1688, 1695, 1700, 1707, 1712, 1719, 1724 },

   };

#if DEBUG
/*
 * Convert bit vector to hex dump format and print
 */
static inline void
dump_cw(const voice_codeword& cw, int len, FILE* fp)  // len in bytes
{
        int i, j;
        for (i = 0; i < len; i++){
                int p = 0;
                for (j = 0; j <  8; j++){
                        p = (p << 1) + cw[ i*8 + j ];
                }
                fprintf(fp, "%02x ", p);
                if (!((i+1) % 16))
                        fprintf(fp, "\n");
        }
        fprintf(fp, "\n");
}
#endif

static inline void
imbe_store_bits(voice_codeword& cw, int s, int l, uint32_t v)
{
	for (int i = l-1; i >= s; i--) {
		cw[i] = v & 1;
		v >>= 1;
	}
}

static inline uint32_t
pngen15(uint32_t& Pr)
{
   int n = 0;
   for(int i = 14; i >= 0; --i) {
      Pr = (173 * Pr + 13849) & 0xffffu;
      if(Pr & 32768) {
         n += (1 << i);
      }
   }
   return n;
}

static inline uint32_t
pngen23(uint32_t& Pr)
{
   int n = 0;
   for(int i = 22; i >= 0; --i) {
      Pr = (173 * Pr + 13849) & 0xffffu;
      if(Pr & 32768) {
         n += (1 << i);
      }
   }
   return  n;
}

/* APCO IMBE header decoder.
 *
 * extracts 88 bits of IMBE parameters given an input 144-bit frame
 *
 * \param cw Codeword containing bits to be decoded
 * \param u0-u7 Result output vectors
 */

static inline size_t
imbe_header_decode(const voice_codeword& cw, uint32_t& u0, uint32_t& u1, uint32_t& u2, uint32_t& u3, uint32_t& u4, uint32_t& u5, uint32_t& u6, uint32_t& u7, uint32_t& E0, uint32_t& ET)
{
   size_t errs = 0;
   uint32_t v0 = extract(cw, 0, 23);
   errs = golay_23_decode(v0);
   u0 = v0;
   E0 = errs;

   uint32_t pn = u0 << 4;
   uint32_t m1 = pngen23(pn);
   uint32_t v1 = extract(cw, 23, 46) ^ m1;
   errs += golay_23_decode(v1);
   u1 = v1;

   uint32_t m2 = pngen23(pn);
   uint32_t v2 = extract(cw, 46, 69) ^ m2;
   errs += golay_23_decode(v2);
   u2 = v2;

   uint32_t m3 = pngen23(pn);
   uint32_t v3 = extract(cw, 69, 92) ^ m3;
   errs += golay_23_decode(v3);
   u3 = v3;

   uint32_t m4 = pngen15(pn);
   uint16_t v4 = extract(cw, 92, 107) ^ m4;
   errs += hamming_15_decode(v4);
   u4 = v4;

   uint32_t m5 = pngen15(pn);
   uint16_t v5 = extract(cw, 107, 122) ^ m5;
   errs += hamming_15_decode(v5);
   u5 = v5;

   uint32_t m6 = pngen15(pn);
   uint16_t v6 = extract(cw, 122, 137) ^ m6;
   errs += hamming_15_decode(v6);
   u6 = v6;

   u7 = extract(cw, 137, 144);
   u7 <<= 1; /* so that bit0 is free (see note about BOT bit */
   ET = errs;
   return errs;
}

/*
 * Pack 88 bit IMBE parameters into uint8_t vector
 */
static inline void
imbe_pack(packed_codeword& cw, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3, uint32_t u4, uint32_t u5, uint32_t u6, uint32_t u7)
{
	cw.empty();
	cw.push_back(u0 >> 4);
	cw.push_back(((u0 & 0xf) << 4) + (u1 >> 8));
	cw.push_back(u1 & 0xff);
	cw.push_back(u2 >> 4);
	cw.push_back(((u2 & 0xf) << 4) + (u3 >> 8));
	cw.push_back(u3 & 0xff);
	cw.push_back(u4 >> 3);
	cw.push_back(((u4 & 0x7) << 5) + (u5 >> 6));
	cw.push_back(((u5 & 0x3f) << 2) + (u6 >> 9));
	cw.push_back(u6 >> 1);
	cw.push_back(((u6 & 0x1) << 7) + (u7 >> 1));
}

/* APCO IMBE header encoder.
 *
 * given 88 bits of IMBE parameters, construct output 144-bit IMBE codeword
 *
 * \param cw Codeword into which 144 bits of results are placed
 * \param u0-u7 input parameters
 */

static inline void
imbe_header_encode(voice_codeword& cw, uint32_t u0, uint32_t u1, uint32_t u2, uint32_t u3, uint32_t u4, uint32_t u5, uint32_t u6, uint32_t u7)
{
	// given input 88-bit IMBE frame (in u0-u7),
	// add golay / hamming bits to produce a 144-bit frame.
	uint32_t c0, c1, c2, c3, c4, c5, c6, c7;

	uint32_t pn = u0 << 4;

	c0 = golay_23_encode(u0);
	imbe_store_bits(cw, 0, 23, c0);

	uint32_t m1 = pngen23(pn);
	c1 = golay_23_encode(u1) ^ m1;
	imbe_store_bits(cw, 23, 46, c1);

	uint32_t m2 = pngen23(pn);
	c2 = golay_23_encode(u2) ^ m2;
	imbe_store_bits(cw, 46, 69, c2);

	uint32_t m3 = pngen23(pn);
	c3 = golay_23_encode(u3) ^ m3;
	imbe_store_bits(cw, 69, 92, c3);

	uint32_t m4 = pngen15(pn);
	c4 = hamming_15_encode(u4) ^ m4;
	imbe_store_bits(cw, 92, 107, c4);

	uint32_t m5 = pngen15(pn);
	c5 = hamming_15_encode(u5) ^ m5;
	imbe_store_bits(cw, 107, 122, c5);

	uint32_t m6 = pngen15(pn);
	c6 = hamming_15_encode(u6) ^ m6;
	imbe_store_bits(cw, 122, 137, c6);

	c7 = u7;
	imbe_store_bits(cw, 137, 144, c7 >> 1);
}

static inline void
imbe_deinterleave (const_bit_vector& frame_body, voice_codeword& cw, uint32_t frame_nr)
{
      for(size_t j = 0; j < voice_codeword_sz; ++j) {
         cw[j] = frame_body[voice_codeword_bits[frame_nr][j]];
      }
}


static inline void
imbe_interleave(bit_vector& frame_body, const voice_codeword& cw, uint32_t frame_nr)
{
      for(size_t j = 0; j < voice_codeword_sz; ++j) {
         frame_body[voice_codeword_bits[frame_nr][j]] = cw[j];
      }
}

static inline void
imbe_frame_unpack(uint8_t *A, uint32_t& u0, uint32_t& u1, uint32_t& u2, uint32_t& u3, uint32_t& u4, uint32_t& u5, uint32_t& u6, uint32_t& u7, uint32_t& E0, uint32_t& ET)
{
   E0 = A[0];
   ET = A[1];
   u0 = A[4] + (E0 & 240) * 16;
   u1 = A[5] + (E0 & 15) * 256;
   u2 = A[6] + (ET & 240) * 16;
   u3 = A[7] + (ET & 15) * 256;
   E0 = A[2];
   ET = A[3];
   u4 = A[8] + (E0 & 224) * 8;
   u5 = A[9] + (E0 & 28) * 64;
   u6 = A[10] + (ET & 128) * 2 + (E0 & 3) * 512;
   u7 = ET & 127;
   E0 = A[11];
   //if(E0 & 192) exit(4);
   if(E0 & 192) return;
   ET = E0 & 3;
   E0 = (E0 & 84) / 4;
}

/*
 * Given a 144-bit IMBE frame(cw),
 * 1. Decode frame to error-corrected 88-bit format
 * 2. Re-encode frame into 144-bit format with refreshed Hamming/Golay encoding
 * 3. FIXME: track decoding error rates and stats
 */
static inline void
imbe_regenerate_frame(bit_vector& cw) {
        unsigned int u0 = 0;
        unsigned int u1,u2,u3,u4,u5,u6,u7;
        unsigned int E0 = 0;
        unsigned int ET = 0;

        // PN/Hamming/Golay - etc.
        imbe_header_decode(cw, u0, u1, u2, u3, u4, u5, u6, u7, E0, ET) ;
#if DEBUG
	printf("u_0: %x\r\nu_1: %x\r\nu_2: %x\r\nu_3: %x\r\nu_4: %x\r\nu_5: %x\r\nu_6: %x\r\nu_7: %x\r\n\r\n", u0, u1, u2, u3, u4, u5, u6, u7>>1);
#endif
        imbe_header_encode(cw, u0, u1, u2, u3, u4, u5, u6, u7);
}

/*
 * process voice units (ldu1 or ldu2)
 * perform error correction for each of the nine embedded 144-bit frames
 * by regenerating the error-correction coding bits
 */
static inline void
imbe_regenerate_voice_unit(bit_vector& frame_body) {
	voice_codeword cw(voice_codeword_sz);
#if DEBUG
	dump_cw(frame_body, 216, stderr);
#endif
	for(size_t i = 0; i < nof_voice_codewords; ++i) {
		imbe_deinterleave(frame_body, cw, i);
		imbe_regenerate_frame(cw);
		imbe_interleave(frame_body, cw, i);
	}
#if DEBUG
	dump_cw(frame_body, 216, stderr);
#endif
}

#endif /* INCLUDED_IMBE_FRAME_H */
