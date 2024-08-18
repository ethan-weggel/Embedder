word = "The"
hotVector = [1, 0, 0, 0, 0, 0, 0, 0]
weightVector = [[0.0170565, -0.0019518, -0.00421828, 0.0147468, -0.00395841, -0.0160955, 0.00552959, 0.00750907, 0.00450906, -0.00612247, 0.0264421, 0.00890978, 0.00826106, -0.00932086, -0.00751865, 0.00807844, 0.00166886, 0.0346669, -0.00558261, -0.00783661, 0.00814, -0.00889655, 0.00927354, -0.00440134, -0.00880756, 0.00131273, 0.0155656, -0.00255532, -0.0128954, 0.00233686, 0.0118133, -0.00641143, 0.00296719, 0.0120641, -0.0140247, -0.00364047, 0.00855616, -0.00691659, 0.00602212, 0.00350331, 0.00813516, 0.00971747, -0.0065562, 0.0200949, 0.0074165, 0.019796, -0.00982047, 0.0193438, -0.00335142, -0.00237727],
[-0.00140328, -0.00140068, -0.011369, 0.00210655, -0.0167992, 0.0237342, -0.0156418, 0.0167413, 0.00796318, 0.0147672, -0.0142003, 0.00535724, 0.0132864, -0.0156892, 0.00735425, 0.00880019, 0.00684343, -0.0148869, -0.0088357, -0.00711452, -0.0128882, -0.00565881, 0.000611747, -0.0043389, -0.00571111, -7.75064e-05, -0.000949831, -0.00233496, -0.00891329, 0.0132892, 0.0074323, 0.00302937, -0.00986029, -0.00376566, -0.001025, 0.00946934, 0.0013959, -0.0104491, 0.00247142, -0.0149835, -0.0215166, -0.0125196, 0.00313575, 0.00755598, -0.00549252, -0.0159832, 5.69768e-05, -0.00244657, 0.00521257, -0.00323383],
[-0.0105714, 0.00648253, -0.00324426, 0.00916187, -0.00506286, 0.00740692, 0.00161691, -0.0203311, 0.00384539, 0.00234412, -0.0137553, 0.002268, 0.000208352, 0.00865827, -0.00956841, 0.00240237, -0.00679284, 0.00638717, -0.00465498, 0.00224712, 0.0147791, 0.00756132, 0.00309196, 0.000104251, 0.0105868, 0.00762044, -0.026556, 0.0125165, 0.010923, -0.0158649, -0.0100071, -0.0102231, 0.0114301, 0.0177631, 0.0127733, -0.0126156, 0.00207946, -0.00574754, -0.00198865, 0.00122658, -0.0047458, -0.00491773, -0.00967385, -0.00719163, 0.00515231, 0.00151452, 0.00613739, 0.00331646, 0.00279395, 0.0115588],
[-0.0139215, 0.000398869, -0.000798795, 0.00487147, 0.00119307, -0.00194373, 0.000293788, -0.00835974, 0.0178758, -0.00384431, -0.00366662, -0.0159844, 0.011532, -0.00346401, -0.0123653, 0.00368032, 0.00629158, -0.0031287, 0.00941098, -0.00234146, -0.0059971, 0.00516797, -0.000800031, -0.00451305, -0.00219233, -0.00240117, 0.0041634, 0.00276759, -0.0159909, 0.0158925, -0.00257743, -0.000449988, -0.00322004, 0.00853704, 0.00279858, -0.00900621, 0.00193401, -3.98532e-05, 0.00594941, 0.0044093, -0.00355182, 0.00156637, -0.00444314, 0.00135991, -0.00200058, 0.00806864, 0.00903279, -0.00082178, -0.0086067, 0.0102662],
[-0.00171718, 0.0160407, 0.000878954, 0.0193315, -0.00794202, 0.0150026, -0.00177396, -0.00412686, 0.00105948, -0.0063157, -0.00332439, -0.00670152, -0.00526762, -0.0119441, -0.0140095, -0.016677, 0.00266891, 0.0136894, -0.0100085, 0.00416904, 0.00516813, -0.00356215, -0.0122938, 0.00144257, -0.0191089, 0.0030033, 0.0104474, -0.0247313, 0.00942291, -0.00707226, -0.00627801, 0.0170649, -0.0163342, 0.00923038, 0.00472167, 0.00899085, -0.00808717, 0.00903871, -0.0110377, -0.00378043, 0.00897683, -0.0138666, 0.0173199, -0.00374878, -0.00240875, -0.00517697, 0.00402772, -0.0204019, 0.0063168, 0.00341046],
[-0.00618841, 0.0100186, 0.00873122, -0.00512987, 0.00406779, 0.0256355, 0.000827247, 9.19785e-05, -0.0110527, -0.00684822, -0.00555611, -0.0148753, -0.00823917, 0.00354178, -0.000887266, 0.00284404, -0.0116543, 0.00428485, -0.0139725, -0.00132586, 0.00244906, -0.00218972, 0.0245441, 0.00665698, -0.00522503, -0.000259744, -0.00925278, 0.00705677, 0.00475727, 0.0142228, 0.00183264, 0.00807141, -0.0129276, -0.0100582, 0.00987746, 0.00279322, -0.00370094, -0.00324875, -0.0127015, 0.00296122, -0.0146147, 0.0162547, -0.016593, 0.0092919, 0.00787668, -0.00105932, 0.00658661, 0.00931813, -0.00188832, 0.00156001],
[0.0109468, 0.00714774, -0.0142835, -0.00751759, 0.00719907, 0.0022061, -0.00692326, -0.00968775, 0.00643658, 0.00254646, -0.0012815, 0.00467596, -0.0118039, 0.00409279, -0.0119939, -0.00852766, 0.00678174, -0.00715791, 0.0173493, 0.00335953, 0.00722588, -0.00192393, 0.0119721, 0.0114029, -0.00214694, -0.0113075, 0.00314985, 0.00366648, -0.0148055, 0.0022896, 0.000949243, 0.00537826, -0.0221672, -0.00137622, -0.0105478, -0.0309273, -0.00405873, -0.00544418, 0.0211265, 0.0046992, -0.0160802, -0.00115481, 0.00353621, 0.00197438, -0.00120053, 0.00451393, -0.0148806, -3.79348e-05, -0.00021928, 0.00257321],
[0.00531998, 0.0124764, -0.00282743, -0.00111117, 0.00742819, 0.00328893, 0.00534222, 0.0128887, 0.00627341, 0.00831897, -0.0122485, 0.00353329, 0.0137515, 0.000104967, -0.0142213, -0.00869541, 0.00197998, -0.00360749, 0.00105366, -0.00106619, -0.00734963, -0.00842646, -0.00119078, 0.0109848, -0.000325975, 0.00643813, 0.00829631, 0.000641586, 0.00342273, 0.00101907, -0.00608372, 0.0015493, -0.0135508, 0.0102522, -0.00704576, -0.000454291, -0.00447697, -0.0103162, -0.00504356, 0.00478645, 0.00614488, 0.0115691, 0.0121436, -0.00299946, 0.00523897, -0.00271354, -0.0050974, 0.00666893, -0.00781189, -0.00732926]]