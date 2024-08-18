word = "a"
hotVector = [0, 1, 0, 0, 0, 0, 0, 0]
weightVector = [[0.00412165, 0.00204341, -0.0105837, -0.00279851, 0.00352739, -0.0104387, -0.0114716, -0.0119633, 0.0113531, 0.0140307, -0.0220859, -0.020605, 0.0162345, 0.00512556, 0.000555668, -0.0193616, -0.0139817, -0.000150092, -0.00453856, -0.0139157, -0.00788998, -0.0111828, 0.0145179, -0.00307624, 0.00496553, -0.022449, -0.00326757, -0.0185709, -0.0141348, 0.0161771, -0.000277282, -0.0284898, 0.0014323, -0.00683333, 0.00513128, -0.00353936, -0.0244695, 0.0234993, -0.00303311, 0.00448274, -0.00209336, 0.00295679, 0.0056008, 0.000917786, -0.00589878, 0.00252021, -0.0020659, 0.00584443, -0.0147279, -0.00479857],
[-0.000372837, -0.017144, 0.0225819, 0.00180196, -0.0223622, 0.00258613, 0.0175436, 0.0101863, -0.0186737, -0.00721362, 0.00996201, -0.00337425, -0.0156272, -0.00220508, 0.0133875, -0.000555704, 0.0047722, 0.0026531, 0.00307372, -0.00660286, 0.0046048, 0.020157, 0.00991209, -0.0108678, -0.00656993, -0.00552491, 0.00306779, -0.00295595, -0.00625477, 0.0193157, 0.00264362, -0.0103647, 0.0103591, -0.0047786, 0.00748931, -0.00974649, -0.0120387, -0.000734606, -0.00624882, 0.0100179, 0.00573108, -0.00266274, -0.0143062, -0.00211958, -0.0124404, 0.00421533, 0.00305582, 0.0102148, 0.00851495, 0.00488951],
[-0.0132117, -0.00403216, -0.00781791, 0.012638, -0.00478937, -0.0165585, 0.00524785, 0.00726084, -0.00424719, 0.00227568, -0.00647995, 0.00748113, -0.00638375, 0.0189764, -0.00450643, 0.00577792, -0.00127184, 0.00735139, 0.0102762, 0.00122464, -0.0119149, -0.00743128, -0.00245424, -0.0247108, 0.00586121, 0.0118146, 0.00835699, -0.0149215, 0.00467126, -0.00667573, -0.00196265, -0.00093674, 0.00174002, -0.00583984, -0.0220892, 0.00305006, 0.00897352, -0.00447414, 0.00947021, -0.0031625, -0.00114074, -0.0198209, -0.00502385, -0.00173205, 0.0195223, 0.0100738, -0.00276667, 0.0155609, 0.00904294, 0.0137683],
[-0.00249152, -0.015643, -0.00883492, -0.00278031, 0.0110677, 0.00237925, -0.00827089, -0.00513555, 0.00988145, 0.00678485, -0.00537496, -0.00213604, 0.000623186, -0.0050051, -0.000704123, 0.00486012, -0.000692896, -0.00533209, -0.000410918, 0.0154089, -0.00520237, 0.00549032, 0.00874926, 0.00764448, 0.00662982, 0.00582034, -0.00847436, 0.00532097, -0.00109675, 0.00805757, -0.0101441, -0.00485726, 0.00468992, -0.0044036, -0.00592457, 0.0126015, 0.0153005, -0.0183224, -0.00662043, 0.0127632, -0.0201949, 0.00785095, 0.010072, 0.011906, -0.00734332, -0.00176407, -0.00220551, -0.0180174, 0.00918177, -0.00209658],
[-0.0200814, -0.00114746, -0.0139587, -0.00484087, -0.0132887, -0.0115521, -0.00284197, 0.0027054, -0.0183883, -0.00204834, -0.0135082, -0.0106779, -0.0213804, 0.00247374, 0.00212091, -0.00881387, 0.00584679, 0.00466335, 0.00469368, 0.00178771, 0.00675855, -0.0102032, 0.0153044, 0.0184829, -0.0215974, 0.0118899, -0.00127584, -0.0139497, 0.00389256, -0.0102395, 0.00469293, 0.00239825, 0.000823662, -0.0186361, 0.00589136, 0.00945742, 0.00952851, -0.0294245, -0.00806302, -0.0139582, -0.00776398, 0.00293939, 0.000913946, -0.000468228, 0.0108414, 0.000162263, -0.000734194, -0.00575414, -0.0145934, -0.00548908],
[-0.00380286, -0.00602224, -0.000887593, -0.000281946, 0.000539215, -0.00292189, -0.0283815, 0.00648843, -0.00140454, 0.00336665, -0.00621829, 0.00273202, -0.00356581, -0.00173778, -0.00773136, 0.00619885, -0.0149049, 0.00621059, -0.00628343, -0.000986489, -0.0022547, -0.00106902, 0.0014089, 0.0047857, -0.000305309, -0.00552649, -0.0235875, 0.00644726, 0.0115149, 0.0024996, -0.000856374, -0.00119699, 0.00665792, -0.0117788, 0.0116653, 0.00494478, 0.0026314, -0.00332267, -0.00295181, 0.0182199, -0.00667297, 0.00432166, 0.00824013, -0.00612558, 0.00275354, -0.012124, -0.00283327, 0.00911011, -0.00442405, 0.0121763],
[0.0205184, 0.0104634, 0.0122142, 0.00963606, -0.0130744, 0.00798771, 0.0111571, 0.0011616, -0.00703099, -0.000783169, -0.0102832, 0.00847252, 0.011321, 0.00146975, -0.00412114, -0.00831179, -0.00578595, 0.000435205, -0.00172653, 0.00328758, 0.00551598, -0.0267142, 0.0214868, -0.0105749, 0.00276251, -0.000873301, 0.00924968, 0.00338117, -0.00278664, -0.00760612, -0.0118968, -0.00329668, 0.00874181, -0.00303346, -0.00505786, -0.00547378, 0.00108357, -0.0125421, -0.00937492, -0.00507992, 0.0119805, -0.00843998, -0.00449613, -0.00501909, 0.0074606, 0.00756342, 0.0129211, 0.00597854, 0.00815696, -0.0086459],
[0.00368368, 0.00296934, -0.00591355, 0.0029628, -0.00108072, 0.0104549, 0.0126922, -0.0035441, -0.0010775, 0.00930866, 0.00888006, 0.00946145, -0.0112272, 0.0150815, 0.00284461, -0.000416707, -0.00136995, -0.00560798, -0.00357509, 0.00645199, -0.012651, -0.0075659, -0.000596303, -0.0116263, -0.00491517, -0.0162125, -0.0281152, -0.00627502, 0.000494717, -0.0128689, 0.00270221, 0.00842538, -0.0160194, 0.00912467, -0.00326498, -0.000319473, 0.00136622, -0.0130357, 0.0166822, 0.0150933, -0.00395732, 0.00787643, 0.00726188, -0.00249647, -0.0028341, -0.00761618, -0.00275226, 0.0150224, -0.00998638, 0.00789647]]