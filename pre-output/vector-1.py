word = "man"
hotVector = [0, 0, 0, 0, 0, 0, 1, 0]
weightVector = [[-0.00872253, -0.00957373, -0.0233327, -0.00734453, -0.0060596, 0.00111725, -0.0164157, 0.00676729, 0.0096824, -0.00358237, -0.00530622, -0.00235329, 0.00818776, 0.00231795, -0.0113551, -0.00528669, 0.00814739, -0.0189866, 0.00156094, 0.00501382, 0.00551825, 0.00201696, 0.00797999, 0.000245879, -0.00770938, -0.0115866, 0.00710941, 0.00434291, -0.00512624, 0.00910855, 0.0246133, 0.0164136, -0.00558369, -0.00640036, -0.000827734, -0.00142819, -0.0150662, 0.00241148, 0.0155446, -0.00662334, 0.00256896, 0.00596978, 0.00772165, 0.00303696, 0.0024649, 4.06868e-05, 1.36384e-05, -0.0142008, 0.00754792, 0.00965655],
[-0.00234292, 0.00844659, 0.00198951, -0.00196524, 0.00408821, -0.00635675, -0.00547498, 0.00603321, -0.000131048, 0.00301254, 0.0131459, 0.0109624, 0.0104217, -0.00569141, -0.0124339, -0.00815468, -0.0063459, 0.0201789, 0.0181701, 0.00538739, 0.00212334, -0.00673641, -0.00965653, 0.00941469, 0.00723623, 0.00978301, 0.0168902, -0.00840163, 0.0154459, -0.000555451, -0.00792114, -0.00419817, -0.0098868, -0.0082053, -0.0026554, 0.00496121, -0.0149776, -0.00705787, -0.00590619, -0.0127378, -0.0135624, 0.00546761, 0.0028905, 0.00284165, -0.00126693, -0.0169062, -0.0096375, 0.0066546, 0.0166275, -0.00787712],
[-0.00343874, -0.0138567, -0.00510648, -0.0135531, -0.0113667, 0.00183872, 0.00517194, 0.00597207, -0.0101859, 0.00967029, -0.00300532, 0.0171868, -0.00971509, 0.00889833, 0.00333222, 0.0237091, -0.0142682, -0.00172148, -0.00796926, 0.00410278, -0.00793374, 0.00219554, 0.00661402, 0.00160692, 0.00368814, -0.00284193, 0.00517386, 0.00426112, 0.000210027, -0.00764702, 0.00144516, 0.0108174, 0.0247538, -0.00508637, 0.000693269, -0.00341322, 0.0043304, 0.00702774, 0.00102413, 0.0104335, 0.0105344, 0.0018879, 0.00327276, -0.00988051, -0.00207757, -0.0141813, -0.0133327, -0.0076206, -0.00389481, 0.0113955],
[0.00959685, -0.00237297, -0.00949923, 0.00460701, -0.0074427, 0.00597902, -0.016041, -0.00717484, 0.0166366, 0.00527677, -0.013065, -0.00843594, -0.00928382, 0.00244037, 0.00309426, 0.0013088, 0.00385219, -0.010722, -0.0123822, 0.00745862, -0.00412385, -0.0104974, 0.000636294, -0.00501912, 0.000977081, -0.00316621, -0.0109271, -0.00919141, -0.00485563, 0.00220186, 0.0262662, 0.0186768, -0.0105525, -0.010512, 0.0171136, 0.0122601, 0.00464279, 0.00176576, -0.00466641, 0.0172301, -0.00566721, -0.00280335, -0.00682618, 0.00575934, 0.0166349, -0.00704877, -0.00365927, 0.000603126, -0.0016638, 0.0153169],
[0.0105806, -0.0103142, 0.00873645, -0.00470962, -0.0129911, -0.00889485, 0.00600802, -0.00527814, 0.000224271, -0.00496545, 0.00524167, -0.00886507, 0.0151336, -0.00217529, 0.00756981, -0.00883911, -0.00181899, -0.00235439, 0.000798005, -0.00162588, -0.0168728, -0.00700459, -0.00428893, -0.00334574, 0.012134, 0.00260296, 0.00101543, -0.00709609, -0.0218995, -0.0136368, 0.00387612, -0.0199612, -0.00343522, -0.0243093, 0.0155832, 0.0152265, 0.0100498, 0.0155649, -0.0185677, -0.00986145, -0.0229555, -0.00775735, 0.00818973, 0.000805103, 0.00724052, -0.00408979, -0.0136501, 0.00873451, -0.00391165, 0.00661696],
[-0.00994774, 0.00776625, 0.00847312, -0.00303985, -0.00585104, 0.00189569, -0.00300995, 0.00479573, -0.0109411, 0.00613357, 0.0163115, -0.0154403, -0.00668814, 0.00175852, -0.013881, 0.00679585, -0.00547584, 0.00100116, -0.0135009, 0.00231458, 0.0100268, -0.00752268, -0.0171216, -0.00969651, -0.0208567, -0.00573095, 0.00107548, 0.00629998, 0.00104618, -0.0103523, -0.00190292, -0.00234729, 0.0245396, -0.0148828, -0.00147956, 0.0017988, -0.0159585, -0.0145756, -0.00552838, 0.00073503, 0.00110173, -0.000109562, -0.00811717, 0.00928196, -0.00263778, 0.00227943, 0.00529732, -0.0210818, 0.00575273, 0.0155291],
[0.00357398, 0.011403, -0.00590932, -0.010756, 0.0071194, -0.0118818, 0.00656823, -0.00212661, -0.00315308, 0.00123337, -0.000461692, 0.00409669, 0.000952173, 0.0011365, -0.00526742, -0.0159455, 0.0109407, -0.00942644, -0.00167299, -0.00672656, -0.00159773, 0.00468839, -0.00091425, -0.0124742, -0.00581689, -0.00625767, -0.00786981, -0.00213458, -0.00941785, -0.0220997, -0.00866367, -0.0107864, -0.0017629, -0.0121305, -0.0136749, -0.00813997, 0.00199804, 0.0144463, -0.00657446, -0.0152857, -0.0081909, -0.00200105, -0.011881, -0.00746244, -0.00014879, 0.00367417, -0.0128502, -0.00607055, -0.011266, 0.00409272],
[-0.00938656, 0.000136119, -0.00625917, -0.00590828, 0.0207069, 0.0042112, -0.00437853, -0.00545097, 0.00256625, 0.00155311, 0.00699204, 0.00342028, -0.00440429, -0.00265895, 0.0163981, -0.00437447, -0.00218666, -0.00458284, -0.00447864, -0.0108825, -0.00357428, -0.00436588, -0.0104843, -0.0175586, 0.0031319, 0.0044609, 0.000945759, 0.00430763, 0.0033561, -0.0106539, 0.00189752, 0.00834847, 0.0118237, 0.0195729, -0.0121643, -0.0204019, 0.00315876, 0.0203307, 0.0050857, -0.00364, 0.0139558, 0.00335773, 0.00694326, 0.0182062, 0.000663029, 0.00206385, 0.00140429, -0.0100845, 0.0118082, -0.00437483]]