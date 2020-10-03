/* AlinousLangTokenManager.cc */
#include "AlinousLangTokenManager.h"
#include "TokenMgrError.h"
namespace alinouslang {
static const unsigned long long jjbitVec0[] = {
   0xfffffffffffffffeULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL
};
static const unsigned long long jjbitVec2[] = {
   0x0ULL, 0x0ULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL
};
static const int jjnextStates[] = {
   26, 27, 13, 30, 31, 34, 35, 41, 43, 51, 52, 54, 15, 16, 18, 1, 
   4, 5, 7, 3, 62, 69, 5, 7, 3, 9, 10, 13, 15, 16, 20, 18, 
   26, 27, 13, 36, 37, 13, 51, 52, 54, 51, 52, 56, 54, 51, 52, 60, 
   54, 63, 64, 70, 71, 72, 11, 12, 17, 19, 21, 28, 29, 32, 33, 38, 
   39, 44, 45, 47, 49, 53, 55, 57, 59, 65, 66, 67, 68, 73, 74, 
};
static JJChar jjstrLiteralChars_0[] = {0};
static JJChar jjstrLiteralChars_1[] = {0};
static JJChar jjstrLiteralChars_2[] = {0};
static JJChar jjstrLiteralChars_3[] = {0};
static JJChar jjstrLiteralChars_4[] = {0};
static JJChar jjstrLiteralChars_5[] = {0};
static JJChar jjstrLiteralChars_6[] = {0};

static JJChar jjstrLiteralChars_7[] = {0};
static JJChar jjstrLiteralChars_8[] = {0};
static JJChar jjstrLiteralChars_9[] = {0};
static JJChar jjstrLiteralChars_10[] = {0};
static JJChar jjstrLiteralChars_11[] = {0};
static JJChar jjstrLiteralChars_12[] = {0};
static JJChar jjstrLiteralChars_13[] = {0};
static JJChar jjstrLiteralChars_14[] = {0};
static JJChar jjstrLiteralChars_15[] = {0};
static JJChar jjstrLiteralChars_16[] = {0};
static JJChar jjstrLiteralChars_17[] = {0};
static JJChar jjstrLiteralChars_18[] = {0};
static JJChar jjstrLiteralChars_19[] = {0};
static JJChar jjstrLiteralChars_20[] = {0};

static JJChar jjstrLiteralChars_21[] = {0x3b, 0};
static JJChar jjstrLiteralChars_22[] = {0x3d, 0};

static JJChar jjstrLiteralChars_23[] = {0x2a, 0};
static JJChar jjstrLiteralChars_24[] = {0x2b, 0x2b, 0};

static JJChar jjstrLiteralChars_25[] = {0x2b, 0};
static JJChar jjstrLiteralChars_26[] = {0x2d, 0x2d, 0};

static JJChar jjstrLiteralChars_27[] = {0x2d, 0};
static JJChar jjstrLiteralChars_28[] = {0x2f, 0};

static JJChar jjstrLiteralChars_29[] = {0x25, 0};
static JJChar jjstrLiteralChars_30[] = {0x26, 0x26, 0};

static JJChar jjstrLiteralChars_31[] = {0x7c, 0x7c, 0};
static JJChar jjstrLiteralChars_32[] = {0x26, 0};

static JJChar jjstrLiteralChars_33[] = {0x7c, 0};
static JJChar jjstrLiteralChars_34[] = {0x28, 0};

static JJChar jjstrLiteralChars_35[] = {0x29, 0};
static JJChar jjstrLiteralChars_36[] = {0x5b, 0};

static JJChar jjstrLiteralChars_37[] = {0x5d, 0};
static JJChar jjstrLiteralChars_38[] = {0x24, 0};

static JJChar jjstrLiteralChars_39[] = {0x2e, 0};
static JJChar jjstrLiteralChars_40[] = {0x2c, 0};

static JJChar jjstrLiteralChars_41[] = {0x40, 0x40, 0};
static JJChar jjstrLiteralChars_42[] = {0x40, 0};

static JJChar jjstrLiteralChars_43[] = {0x7b, 0};
static JJChar jjstrLiteralChars_44[] = {0x7d, 0};

static JJChar jjstrLiteralChars_45[] = {0x3d, 0x3d, 0};
static JJChar jjstrLiteralChars_46[] = {0x21, 0x3d, 0};

static JJChar jjstrLiteralChars_47[] = {0x3e, 0};
static JJChar jjstrLiteralChars_48[] = {0x3e, 0x3d, 0};

static JJChar jjstrLiteralChars_49[] = {0x3c, 0};
static JJChar jjstrLiteralChars_50[] = {0x3c, 0x3d, 0};

static JJChar jjstrLiteralChars_51[] = {0x21, 0};
static JJChar jjstrLiteralChars_52[] = {0x3a, 0};

static JJChar jjstrLiteralChars_53[] = {0x3e, 0x3e, 0};
static JJChar jjstrLiteralChars_54[] = {0x3e, 0x3e, 0x3e, 0};

static JJChar jjstrLiteralChars_55[] = {0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74, 0};

static JJChar jjstrLiteralChars_56[] = {0x70, 0x61, 0x63, 0x6b, 0x61, 0x67, 0x65, 0};
static JJChar jjstrLiteralChars_57[] = {0x63, 0x6c, 0x61, 0x73, 0x73, 0};

static JJChar jjstrLiteralChars_58[] = {0x69, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0};

static JJChar jjstrLiteralChars_59[] = {0x61, 0x62, 0x73, 0x74, 0x72, 0x61, 0x63, 0x74, 0};
static JJChar jjstrLiteralChars_60[] = {0x62, 0x72, 0x65, 0x61, 0x6b, 0};

static JJChar jjstrLiteralChars_61[] = {0x62, 0x6f, 0x6f, 0x6c, 0x65, 0x61, 0x6e, 0};
static JJChar jjstrLiteralChars_62[] = {0x62, 0x79, 0x74, 0x65, 0};

static JJChar jjstrLiteralChars_63[] = {0x63, 0x68, 0x61, 0x72, 0};
static JJChar jjstrLiteralChars_64[] = {0x73, 0x68, 0x6f, 0x72, 0x74, 0};

static JJChar jjstrLiteralChars_65[] = {0x69, 0x6e, 0x74, 0};
static JJChar jjstrLiteralChars_66[] = {0x6c, 0x6f, 0x6e, 0x67, 0};

static JJChar jjstrLiteralChars_67[] = {0x53, 0x74, 0x72, 0x69, 0x6e, 0x67, 0};
static JJChar jjstrLiteralChars_68[] = {0x76, 0x61, 0x72, 0};

static JJChar jjstrLiteralChars_69[] = {0x63, 0x61, 0x73, 0x65, 0};
static JJChar jjstrLiteralChars_70[] = {0x63, 0x61, 0x74, 0x63, 0x68, 0};

static JJChar jjstrLiteralChars_71[] = {0x63, 0x6f, 0x6e, 0x73, 0x74, 0};

static JJChar jjstrLiteralChars_72[] = {0x63, 0x6f, 0x6e, 0x74, 0x69, 0x6e, 0x75, 0x65, 0};
static JJChar jjstrLiteralChars_73[] = {0x64, 0x6f, 0};

static JJChar jjstrLiteralChars_74[] = {0x65, 0x6c, 0x73, 0x65, 0};

static JJChar jjstrLiteralChars_75[] = {0x65, 0x78, 0x74, 0x65, 0x6e, 0x64, 0x73, 0};

static JJChar jjstrLiteralChars_76[] = {0x66, 0x69, 0x6e, 0x61, 0x6c, 0x6c, 0x79, 0};
static JJChar jjstrLiteralChars_77[] = {0x66, 0x6f, 0x72, 0};

static JJChar jjstrLiteralChars_78[] = {0x67, 0x6f, 0x74, 0x6f, 0};
static JJChar jjstrLiteralChars_79[] = {0x69, 0x66, 0};

static JJChar jjstrLiteralChars_80[] = {0x69, 0x6d, 0x70, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0};

static JJChar jjstrLiteralChars_81[] = {0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x6f, 0x66, 0};
static JJChar jjstrLiteralChars_82[] = {0x6e, 0x65, 0x77, 0};

static JJChar jjstrLiteralChars_83[] = {0x70, 0x72, 0x69, 0x76, 0x61, 0x74, 0x65, 0};

static JJChar jjstrLiteralChars_84[] = {0x70, 0x72, 0x6f, 0x74, 0x65, 0x63, 0x74, 0x65, 0x64, 0};
static JJChar jjstrLiteralChars_85[] = {0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0};

static JJChar jjstrLiteralChars_86[] = {0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0};
static JJChar jjstrLiteralChars_87[] = {0x73, 0x74, 0x61, 0x74, 0x69, 0x63, 0};

static JJChar jjstrLiteralChars_88[] = {0x73, 0x75, 0x70, 0x65, 0x72, 0};
static JJChar jjstrLiteralChars_89[] = {0x73, 0x77, 0x69, 0x74, 0x63, 0x68, 0};

static JJChar jjstrLiteralChars_90[] = {0x73, 0x79, 0x6e, 0x63, 0x68, 0x72, 0x6f, 0x6e, 0x69, 0x7a, 0x65, 0x64, 0};
static JJChar jjstrLiteralChars_91[] = {0x74, 0x68, 0x69, 0x73, 0};

static JJChar jjstrLiteralChars_92[] = {0x74, 0x68, 0x72, 0x6f, 0x77, 0};
static JJChar jjstrLiteralChars_93[] = {0x74, 0x68, 0x72, 0x6f, 0x77, 0x73, 0};

static JJChar jjstrLiteralChars_94[] = {0x74, 0x72, 0x79, 0};
static JJChar jjstrLiteralChars_95[] = {0x76, 0x6f, 0x69, 0x64, 0};

static JJChar jjstrLiteralChars_96[] = {0x77, 0x68, 0x69, 0x6c, 0x65, 0};

static JJChar jjstrLiteralChars_97[] = {0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0};
static JJChar jjstrLiteralChars_98[] = {0x74, 0x72, 0x75, 0x65, 0};

static JJChar jjstrLiteralChars_99[] = {0x66, 0x61, 0x6c, 0x73, 0x65, 0};
static JJChar jjstrLiteralChars_100[] = {0};
static JJChar jjstrLiteralChars_101[] = {0};
static JJChar jjstrLiteralChars_102[] = {0};
static JJChar jjstrLiteralChars_103[] = {0};
static JJChar jjstrLiteralChars_104[] = {0};
static JJChar jjstrLiteralChars_105[] = {0};
static JJChar jjstrLiteralChars_106[] = {0};
static JJChar jjstrLiteralChars_107[] = {0};
static JJChar jjstrLiteralChars_108[] = {0};
static JJChar jjstrLiteralChars_109[] = {0};
static JJChar jjstrLiteralChars_110[] = {0};
static JJChar jjstrLiteralChars_111[] = {0};
static JJChar jjstrLiteralChars_112[] = {0};

static JJChar jjstrLiteralChars_113[] = {0};
static JJChar jjstrLiteralChars_114[] = {0};
static JJChar jjstrLiteralChars_115[] = {0};
static JJChar jjstrLiteralChars_116[] = {0};
static JJChar jjstrLiteralChars_117[] = {0};
static JJChar jjstrLiteralChars_118[] = {0};
static JJChar jjstrLiteralChars_119[] = {0};
static JJChar jjstrLiteralChars_120[] = {0};
static JJChar jjstrLiteralChars_121[] = {0};
static JJChar jjstrLiteralChars_122[] = {0};
static JJChar jjstrLiteralChars_123[] = {0};
static JJChar jjstrLiteralChars_124[] = {0};
static JJChar jjstrLiteralChars_125[] = {0};
static JJChar jjstrLiteralChars_126[] = {0};

static JJChar jjstrLiteralChars_127[] = {0};
static JJChar jjstrLiteralChars_128[] = {0};
static JJChar jjstrLiteralChars_129[] = {0};
static JJChar jjstrLiteralChars_130[] = {0};
static JJChar jjstrLiteralChars_131[] = {0};
static JJChar jjstrLiteralChars_132[] = {0};
static JJChar jjstrLiteralChars_133[] = {0};
static JJChar jjstrLiteralChars_134[] = {0};
static JJChar jjstrLiteralChars_135[] = {0};
static JJChar jjstrLiteralChars_136[] = {0};
static JJChar jjstrLiteralChars_137[] = {0};
static JJChar jjstrLiteralChars_138[] = {0};
static JJChar jjstrLiteralChars_139[] = {0};
static JJChar jjstrLiteralChars_140[] = {0};

static JJChar jjstrLiteralChars_141[] = {0};
static JJChar jjstrLiteralChars_142[] = {0};
static JJChar jjstrLiteralChars_143[] = {0};
static JJChar jjstrLiteralChars_144[] = {0};
static JJChar jjstrLiteralChars_145[] = {0};
static JJChar jjstrLiteralChars_146[] = {0};
static JJChar jjstrLiteralChars_147[] = {0};
static JJChar jjstrLiteralChars_148[] = {0};
static JJChar jjstrLiteralChars_149[] = {0};
static JJChar jjstrLiteralChars_150[] = {0};
static JJChar jjstrLiteralChars_151[] = {0};
static JJChar jjstrLiteralChars_152[] = {0};
static JJChar jjstrLiteralChars_153[] = {0};
static JJChar jjstrLiteralChars_154[] = {0};

static JJChar jjstrLiteralChars_155[] = {0};
static JJChar jjstrLiteralChars_156[] = {0};
static JJChar jjstrLiteralChars_157[] = {0};
static JJChar jjstrLiteralChars_158[] = {0};
static JJChar jjstrLiteralChars_159[] = {0};
static JJChar jjstrLiteralChars_160[] = {0};
static JJChar jjstrLiteralChars_161[] = {0};
static JJChar jjstrLiteralChars_162[] = {0};
static JJChar jjstrLiteralChars_163[] = {0};
static JJChar jjstrLiteralChars_164[] = {0};
static JJChar jjstrLiteralChars_165[] = {0};
static JJChar jjstrLiteralChars_166[] = {0};
static JJChar jjstrLiteralChars_167[] = {0};
static JJChar jjstrLiteralChars_168[] = {0};

static JJChar jjstrLiteralChars_169[] = {0};
static JJChar jjstrLiteralChars_170[] = {0};
static JJChar jjstrLiteralChars_171[] = {0};
static JJChar jjstrLiteralChars_172[] = {0};
static JJChar jjstrLiteralChars_173[] = {0};
static JJChar jjstrLiteralChars_174[] = {0};
static JJChar jjstrLiteralChars_175[] = {0};
static JJChar jjstrLiteralChars_176[] = {0};
static JJChar jjstrLiteralChars_177[] = {0};
static JJChar jjstrLiteralChars_178[] = {0};
static JJChar jjstrLiteralChars_179[] = {0};
static JJChar jjstrLiteralChars_180[] = {0};
static JJChar jjstrLiteralChars_181[] = {0};
static JJChar jjstrLiteralChars_182[] = {0};

static JJChar jjstrLiteralChars_183[] = {0};
static JJChar jjstrLiteralChars_184[] = {0};
static JJChar jjstrLiteralChars_185[] = {0};
static JJChar jjstrLiteralChars_186[] = {0};
static JJChar jjstrLiteralChars_187[] = {0};
static JJChar jjstrLiteralChars_188[] = {0};
static JJChar jjstrLiteralChars_189[] = {0};
static JJChar jjstrLiteralChars_190[] = {0};

static JJChar jjstrLiteralChars_191[] = {0x5e, 0};
static JJChar jjstrLiteralChars_192[] = {0x3c, 0x3c, 0};

static JJChar jjstrLiteralChars_193[] = {0x7e, 0};
static JJChar jjstrLiteralChars_194[] = {0x3c, 0x3e, 0};
static const JJString jjstrLiteralImages[] = {
jjstrLiteralChars_0, 
jjstrLiteralChars_1, 
jjstrLiteralChars_2, 
jjstrLiteralChars_3, 
jjstrLiteralChars_4, 
jjstrLiteralChars_5, 
jjstrLiteralChars_6, 
jjstrLiteralChars_7, 
jjstrLiteralChars_8, 
jjstrLiteralChars_9, 
jjstrLiteralChars_10, 
jjstrLiteralChars_11, 
jjstrLiteralChars_12, 
jjstrLiteralChars_13, 
jjstrLiteralChars_14, 
jjstrLiteralChars_15, 
jjstrLiteralChars_16, 
jjstrLiteralChars_17, 
jjstrLiteralChars_18, 
jjstrLiteralChars_19, 
jjstrLiteralChars_20, 
jjstrLiteralChars_21, 
jjstrLiteralChars_22, 
jjstrLiteralChars_23, 
jjstrLiteralChars_24, 
jjstrLiteralChars_25, 
jjstrLiteralChars_26, 
jjstrLiteralChars_27, 
jjstrLiteralChars_28, 
jjstrLiteralChars_29, 
jjstrLiteralChars_30, 
jjstrLiteralChars_31, 
jjstrLiteralChars_32, 
jjstrLiteralChars_33, 
jjstrLiteralChars_34, 
jjstrLiteralChars_35, 
jjstrLiteralChars_36, 
jjstrLiteralChars_37, 
jjstrLiteralChars_38, 
jjstrLiteralChars_39, 
jjstrLiteralChars_40, 
jjstrLiteralChars_41, 
jjstrLiteralChars_42, 
jjstrLiteralChars_43, 
jjstrLiteralChars_44, 
jjstrLiteralChars_45, 
jjstrLiteralChars_46, 
jjstrLiteralChars_47, 
jjstrLiteralChars_48, 
jjstrLiteralChars_49, 
jjstrLiteralChars_50, 
jjstrLiteralChars_51, 
jjstrLiteralChars_52, 
jjstrLiteralChars_53, 
jjstrLiteralChars_54, 
jjstrLiteralChars_55, 
jjstrLiteralChars_56, 
jjstrLiteralChars_57, 
jjstrLiteralChars_58, 
jjstrLiteralChars_59, 
jjstrLiteralChars_60, 
jjstrLiteralChars_61, 
jjstrLiteralChars_62, 
jjstrLiteralChars_63, 
jjstrLiteralChars_64, 
jjstrLiteralChars_65, 
jjstrLiteralChars_66, 
jjstrLiteralChars_67, 
jjstrLiteralChars_68, 
jjstrLiteralChars_69, 
jjstrLiteralChars_70, 
jjstrLiteralChars_71, 
jjstrLiteralChars_72, 
jjstrLiteralChars_73, 
jjstrLiteralChars_74, 
jjstrLiteralChars_75, 
jjstrLiteralChars_76, 
jjstrLiteralChars_77, 
jjstrLiteralChars_78, 
jjstrLiteralChars_79, 
jjstrLiteralChars_80, 
jjstrLiteralChars_81, 
jjstrLiteralChars_82, 
jjstrLiteralChars_83, 
jjstrLiteralChars_84, 
jjstrLiteralChars_85, 
jjstrLiteralChars_86, 
jjstrLiteralChars_87, 
jjstrLiteralChars_88, 
jjstrLiteralChars_89, 
jjstrLiteralChars_90, 
jjstrLiteralChars_91, 
jjstrLiteralChars_92, 
jjstrLiteralChars_93, 
jjstrLiteralChars_94, 
jjstrLiteralChars_95, 
jjstrLiteralChars_96, 
jjstrLiteralChars_97, 
jjstrLiteralChars_98, 
jjstrLiteralChars_99, 
jjstrLiteralChars_100, 
jjstrLiteralChars_101, 
jjstrLiteralChars_102, 
jjstrLiteralChars_103, 
jjstrLiteralChars_104, 
jjstrLiteralChars_105, 
jjstrLiteralChars_106, 
jjstrLiteralChars_107, 
jjstrLiteralChars_108, 
jjstrLiteralChars_109, 
jjstrLiteralChars_110, 
jjstrLiteralChars_111, 
jjstrLiteralChars_112, 
jjstrLiteralChars_113, 
jjstrLiteralChars_114, 
jjstrLiteralChars_115, 
jjstrLiteralChars_116, 
jjstrLiteralChars_117, 
jjstrLiteralChars_118, 
jjstrLiteralChars_119, 
jjstrLiteralChars_120, 
jjstrLiteralChars_121, 
jjstrLiteralChars_122, 
jjstrLiteralChars_123, 
jjstrLiteralChars_124, 
jjstrLiteralChars_125, 
jjstrLiteralChars_126, 
jjstrLiteralChars_127, 
jjstrLiteralChars_128, 
jjstrLiteralChars_129, 
jjstrLiteralChars_130, 
jjstrLiteralChars_131, 
jjstrLiteralChars_132, 
jjstrLiteralChars_133, 
jjstrLiteralChars_134, 
jjstrLiteralChars_135, 
jjstrLiteralChars_136, 
jjstrLiteralChars_137, 
jjstrLiteralChars_138, 
jjstrLiteralChars_139, 
jjstrLiteralChars_140, 
jjstrLiteralChars_141, 
jjstrLiteralChars_142, 
jjstrLiteralChars_143, 
jjstrLiteralChars_144, 
jjstrLiteralChars_145, 
jjstrLiteralChars_146, 
jjstrLiteralChars_147, 
jjstrLiteralChars_148, 
jjstrLiteralChars_149, 
jjstrLiteralChars_150, 
jjstrLiteralChars_151, 
jjstrLiteralChars_152, 
jjstrLiteralChars_153, 
jjstrLiteralChars_154, 
jjstrLiteralChars_155, 
jjstrLiteralChars_156, 
jjstrLiteralChars_157, 
jjstrLiteralChars_158, 
jjstrLiteralChars_159, 
jjstrLiteralChars_160, 
jjstrLiteralChars_161, 
jjstrLiteralChars_162, 
jjstrLiteralChars_163, 
jjstrLiteralChars_164, 
jjstrLiteralChars_165, 
jjstrLiteralChars_166, 
jjstrLiteralChars_167, 
jjstrLiteralChars_168, 
jjstrLiteralChars_169, 
jjstrLiteralChars_170, 
jjstrLiteralChars_171, 
jjstrLiteralChars_172, 
jjstrLiteralChars_173, 
jjstrLiteralChars_174, 
jjstrLiteralChars_175, 
jjstrLiteralChars_176, 
jjstrLiteralChars_177, 
jjstrLiteralChars_178, 
jjstrLiteralChars_179, 
jjstrLiteralChars_180, 
jjstrLiteralChars_181, 
jjstrLiteralChars_182, 
jjstrLiteralChars_183, 
jjstrLiteralChars_184, 
jjstrLiteralChars_185, 
jjstrLiteralChars_186, 
jjstrLiteralChars_187, 
jjstrLiteralChars_188, 
jjstrLiteralChars_189, 
jjstrLiteralChars_190, 
jjstrLiteralChars_191, 
jjstrLiteralChars_192, 
jjstrLiteralChars_193, 
jjstrLiteralChars_194, 
};

/** Lexer state names. */
static const JJChar lexStateNames_arr_0[] = 
{0x44, 0x45, 0x46, 0x41, 0x55, 0x4c, 0x54, 0};
static const JJChar lexStateNames_arr_1[] = 
{0x43, 0x4f, 0x4d, 0x4d, 0};
static const JJChar lexStateNames_arr_2[] = 
{0x4c, 0x5f, 0x43, 0x4f, 0x4d, 0x4d, 0};
static const JJString lexStateNames[] = {
lexStateNames_arr_0, 
lexStateNames_arr_1, 
lexStateNames_arr_2, 
};

/** Lex State array. */
static const int jjnewLexState[] = {
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 0, -1, 0, -1, -1, -1, -1, -1, 
};
static const unsigned long long jjtoToken[] = {
   0xfffffffffffc2201ULL, 0xffffffffffffffffULL, 0x81ffffffffffffffULL, 0x7ULL, 
};
static const unsigned long long jjtoSkip[] = {
   0x1eULL, 0x0ULL, 0x2800000000000000ULL, 0x0ULL, 
};
static const unsigned long long jjtoSpecial[] = {
   0x0ULL, 0x0ULL, 0x2800000000000000ULL, 0x0ULL, 
};

  void  AlinousLangTokenManager::setDebugStream(FILE *ds){ debugStream = ds; }

 int  AlinousLangTokenManager::jjStopAtPos(int pos, int kind){
   jjmatchedKind = kind;
   jjmatchedPos = pos;
   return pos + 1;
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa0_2(){
   switch(curChar)
   {
      case 10:
         return jjStopAtPos(0, 187);
      default :
         return 1;
   }
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa0_0(){
   switch(curChar)
   {
      case 9:
         jjmatchedKind = 2;
         return jjMoveNfa_0(0, 0);
      case 10:
         jjmatchedKind = 3;
         return jjMoveNfa_0(0, 0);
      case 13:
         jjmatchedKind = 4;
         return jjMoveNfa_0(0, 0);
      case 32:
         jjmatchedKind = 1;
         return jjMoveNfa_0(0, 0);
      case 33:
         jjmatchedKind = 51;
         return jjMoveStringLiteralDfa1_0(0x400000000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 36:
         jjmatchedKind = 38;
         return jjMoveNfa_0(0, 0);
      case 37:
         jjmatchedKind = 29;
         return jjMoveNfa_0(0, 0);
      case 38:
         jjmatchedKind = 32;
         return jjMoveStringLiteralDfa1_0(0x40000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 40:
         jjmatchedKind = 34;
         return jjMoveNfa_0(0, 0);
      case 41:
         jjmatchedKind = 35;
         return jjMoveNfa_0(0, 0);
      case 42:
         jjmatchedKind = 23;
         return jjMoveNfa_0(0, 0);
      case 43:
         jjmatchedKind = 25;
         return jjMoveStringLiteralDfa1_0(0x1000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 44:
         jjmatchedKind = 40;
         return jjMoveNfa_0(0, 0);
      case 45:
         jjmatchedKind = 27;
         return jjMoveStringLiteralDfa1_0(0x4000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 46:
         jjmatchedKind = 39;
         return jjMoveNfa_0(0, 0);
      case 47:
         jjmatchedKind = 28;
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x0ULL, 0x600000000000000ULL, 0x0ULL);
      case 58:
         jjmatchedKind = 52;
         return jjMoveNfa_0(0, 0);
      case 59:
         jjmatchedKind = 21;
         return jjMoveNfa_0(0, 0);
      case 60:
         jjmatchedKind = 49;
         return jjMoveStringLiteralDfa1_0(0x4000000000000ULL, 0x0ULL, 0x0ULL, 0x5ULL);
      case 61:
         jjmatchedKind = 22;
         return jjMoveStringLiteralDfa1_0(0x200000000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 62:
         jjmatchedKind = 47;
         return jjMoveStringLiteralDfa1_0(0x61000000000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 64:
         jjmatchedKind = 42;
         return jjMoveStringLiteralDfa1_0(0x20000000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 65:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x2000100000000000ULL, 0x640000090008ULL, 0x0ULL);
      case 66:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x400000000000000ULL, 0x820000000a00ULL, 0x0ULL);
      case 67:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x40000000000000ULL, 0x80000008405000ULL, 0x0ULL);
      case 68:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x4000008000000000ULL, 0x48010ULL, 0x0ULL);
      case 69:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x400000000000ULL, 0xa400000000ULL, 0x0ULL);
      case 70:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x10020000000000ULL, 0x80000000000ULL, 0x0ULL);
      case 71:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x200000000000000ULL, 0x0ULL, 0x0ULL);
      case 72:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x800000000000000ULL, 0x0ULL, 0x0ULL);
      case 73:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x4012000000000ULL, 0x100000500ULL, 0x0ULL);
      case 74:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x20000000000000ULL, 0x0ULL, 0x0ULL);
      case 75:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x0ULL, 0x2000000ULL, 0x0ULL);
      case 76:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x8000a00000000000ULL, 0x40000000ULL, 0x0ULL);
      case 77:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x0ULL, 0x200000ULL, 0x0ULL);
      case 78:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x2000000000000ULL, 0x1000000000044ULL, 0x0ULL);
      case 79:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x1008080000000000ULL, 0x83ULL, 0x0ULL);
      case 80:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x0ULL, 0x8004001000000ULL, 0x0ULL);
      case 82:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x1000000000000ULL, 0x44100890102000ULL, 0x0ULL);
      case 83:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x80001000000008ULL, 0x30001020000020ULL, 0x0ULL);
      case 84:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x0ULL, 0x10000820000ULL, 0x0ULL);
      case 85:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x4000000000ULL, 0x2000204000000ULL, 0x0ULL);
      case 86:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x100000000000000ULL, 0x0ULL, 0x0ULL);
      case 87:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x40000000000ULL, 0x0ULL, 0x0ULL);
      case 91:
         jjmatchedKind = 36;
         return jjMoveNfa_0(0, 0);
      case 93:
         jjmatchedKind = 37;
         return jjMoveNfa_0(0, 0);
      case 94:
         jjmatchedKind = 191;
         return jjMoveNfa_0(0, 0);
      case 97:
         return jjMoveStringLiteralDfa1_0(0x800000000000000ULL, 0x2000100000000000ULL, 0x640000090008ULL, 0x0ULL);
      case 98:
         return jjMoveStringLiteralDfa1_0(0x7000000000000000ULL, 0x400000000000000ULL, 0x820000000a00ULL, 0x0ULL);
      case 99:
         return jjMoveStringLiteralDfa1_0(0x8200000000000000ULL, 0x400000000001e0ULL, 0x80000008405000ULL, 0x0ULL);
      case 100:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x4000008000000200ULL, 0x48010ULL, 0x0ULL);
      case 101:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x400000000c00ULL, 0xa400000000ULL, 0x0ULL);
      case 102:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x10020800003000ULL, 0x80000000000ULL, 0x0ULL);
      case 103:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x200000000004000ULL, 0x0ULL, 0x0ULL);
      case 104:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x800000000000000ULL, 0x0ULL, 0x0ULL);
      case 105:
         return jjMoveStringLiteralDfa1_0(0x480000000000000ULL, 0x4012200038002ULL, 0x100000500ULL, 0x0ULL);
      case 106:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x20000000000000ULL, 0x0ULL, 0x0ULL);
      case 107:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x0ULL, 0x2000000ULL, 0x0ULL);
      case 108:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x8000a00000000004ULL, 0x40000000ULL, 0x0ULL);
      case 109:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x0ULL, 0x200000ULL, 0x0ULL);
      case 110:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x2000000040000ULL, 0x1000000000044ULL, 0x0ULL);
      case 111:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x1008080000000000ULL, 0x83ULL, 0x0ULL);
      case 112:
         return jjMoveStringLiteralDfa1_0(0x100000000000000ULL, 0x380000ULL, 0x8004001000000ULL, 0x0ULL);
      case 114:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x1000000400000ULL, 0x44100890102000ULL, 0x0ULL);
      case 115:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x80001007800001ULL, 0x30001020000020ULL, 0x0ULL);
      case 116:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x478000000ULL, 0x10000820000ULL, 0x0ULL);
      case 117:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x4000000000ULL, 0x2000204000000ULL, 0x0ULL);
      case 118:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x100000080000010ULL, 0x0ULL, 0x0ULL);
      case 119:
         return jjMoveStringLiteralDfa1_0(0x0ULL, 0x40100000000ULL, 0x0ULL, 0x0ULL);
      case 123:
         jjmatchedKind = 43;
         return jjMoveNfa_0(0, 0);
      case 124:
         jjmatchedKind = 33;
         return jjMoveStringLiteralDfa1_0(0x80000000ULL, 0x0ULL, 0x0ULL, 0x0ULL);
      case 125:
         jjmatchedKind = 44;
         return jjMoveNfa_0(0, 0);
      case 126:
         jjmatchedKind = 193;
         return jjMoveNfa_0(0, 0);
      default :
         return jjMoveNfa_0(0, 0);
   }
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa1_0(unsigned long long active0, unsigned long long active1, unsigned long long active2, unsigned long long active3){
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 0);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 38:
         if ((active0 & 0x40000000ULL) != 0L)
         {
            jjmatchedKind = 30;
            jjmatchedPos = 1;
         }
         break;
      case 42:
         if ((active2 & 0x200000000000000ULL) != 0L)
         {
            jjmatchedKind = 185;
            jjmatchedPos = 1;
         }
         break;
      case 43:
         if ((active0 & 0x1000000ULL) != 0L)
         {
            jjmatchedKind = 24;
            jjmatchedPos = 1;
         }
         break;
      case 45:
         if ((active0 & 0x4000000ULL) != 0L)
         {
            jjmatchedKind = 26;
            jjmatchedPos = 1;
         }
         break;
      case 47:
         if ((active2 & 0x400000000000000ULL) != 0L)
         {
            jjmatchedKind = 186;
            jjmatchedPos = 1;
         }
         break;
      case 60:
         if ((active3 & 0x1ULL) != 0L)
         {
            jjmatchedKind = 192;
            jjmatchedPos = 1;
         }
         break;
      case 61:
         if ((active0 & 0x200000000000ULL) != 0L)
         {
            jjmatchedKind = 45;
            jjmatchedPos = 1;
         }
         else if ((active0 & 0x400000000000ULL) != 0L)
         {
            jjmatchedKind = 46;
            jjmatchedPos = 1;
         }
         else if ((active0 & 0x1000000000000ULL) != 0L)
         {
            jjmatchedKind = 48;
            jjmatchedPos = 1;
         }
         else if ((active0 & 0x4000000000000ULL) != 0L)
         {
            jjmatchedKind = 50;
            jjmatchedPos = 1;
         }
         break;
      case 62:
         if ((active0 & 0x20000000000000ULL) != 0L)
         {
            jjmatchedKind = 53;
            jjmatchedPos = 1;
         }
         else if ((active3 & 0x4ULL) != 0L)
         {
            jjmatchedKind = 194;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0x40000000000000ULL, active1, 0L, active2, 0L, active3, 0L);
      case 64:
         if ((active0 & 0x20000000000ULL) != 0L)
         {
            jjmatchedKind = 41;
            jjmatchedPos = 1;
         }
         break;
      case 65:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x902000000000000ULL, active2, 0x8000440020000ULL, active3, 0L);
      case 68:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0L, active2, 0x600000080000ULL, active3, 0L);
      case 69:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x4080809000000000ULL, active2, 0x641200b2140a00ULL, active3, 0L);
      case 70:
         if ((active2 & 0x80ULL) != 0L)
         {
            jjmatchedKind = 135;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0L, active2, 0x40000000001ULL, active3, 0L);
      case 72:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x40000000000ULL, active2, 0x8000020ULL, active3, 0L);
      case 73:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x8001200000000000ULL, active2, 0x10ULL, active3, 0L);
      case 76:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0L, active2, 0x10000ULL, active3, 0L);
      case 78:
         if ((active2 & 0x2ULL) != 0L)
         {
            jjmatchedKind = 129;
            jjmatchedPos = 1;
         }
         else if ((active2 & 0x100ULL) != 0L)
         {
            jjmatchedKind = 136;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x4112000000000ULL, active2, 0x104000000ULL, active3, 0L);
      case 79:
         if ((active2 & 0x800000ULL) != 0L)
         {
            jjmatchedKind = 151;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x20000000000000ULL, active2, 0x80880800603044ULL, active3, 0L);
      case 80:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x4000000000ULL, active2, 0L, active3, 0L);
      case 82:
         if ((active1 & 0x80000000000ULL) != 0L)
         {
            jjmatchedKind = 107;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x1240020000000000ULL, active2, 0x1400100c000ULL, active3, 0L);
      case 83:
         if ((active2 & 0x8ULL) != 0L)
         {
            jjmatchedKind = 131;
            jjmatchedPos = 1;
         }
         else if ((active2 & 0x400ULL) != 0L)
         {
            jjmatchedKind = 138;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x2000400000000000ULL, active2, 0x2000200000000ULL, active3, 0L);
      case 84:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0L, active2, 0x1000000000ULL, active3, 0L);
      case 85:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x18000000000000ULL, active2, 0x11000000000000ULL, active3, 0L);
      case 88:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0L, active2, 0xa000000000ULL, active3, 0L);
      case 89:
         if ((active1 & 0x400000000000000ULL) != 0L)
         {
            jjmatchedKind = 122;
            jjmatchedPos = 1;
         }
         break;
      case 97:
         return jjMoveStringLiteralDfa2_0(active0, 0x100000000000000ULL, active1, 0x902000800000070ULL, active2, 0x8000440020000ULL, active3, 0L);
      case 98:
         return jjMoveStringLiteralDfa2_0(active0, 0x800000000000000ULL, active1, 0L, active2, 0L, active3, 0L);
      case 100:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0L, active2, 0x600000080000ULL, active3, 0L);
      case 101:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x4080809000440000ULL, active2, 0x641200b2140a00ULL, active3, 0L);
      case 102:
         if ((active1 & 0x8000ULL) != 0L)
         {
            jjmatchedKind = 79;
            jjmatchedPos = 1;
         }
         else if ((active2 & 0x80ULL) != 0L)
         {
            jjmatchedKind = 135;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0L, active2, 0x40000000001ULL, active3, 0L);
      case 104:
         return jjMoveStringLiteralDfa2_0(active0, 0x8000000000000000ULL, active1, 0x40138000001ULL, active2, 0x8000020ULL, active3, 0L);
      case 105:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x8001200000001000ULL, active2, 0x10ULL, active3, 0L);
      case 108:
         return jjMoveStringLiteralDfa2_0(active0, 0x200000000000000ULL, active1, 0x400ULL, active2, 0x10000ULL, active3, 0L);
      case 109:
         return jjMoveStringLiteralDfa2_0(active0, 0x80000000000000ULL, active1, 0x10000ULL, active2, 0L, active3, 0L);
      case 110:
         if ((active2 & 0x2ULL) != 0L)
         {
            jjmatchedKind = 129;
            jjmatchedPos = 1;
         }
         else if ((active2 & 0x100ULL) != 0L)
         {
            jjmatchedKind = 136;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0x400000000000000ULL, active1, 0x4112200020002ULL, active2, 0x104000000ULL, active3, 0L);
      case 111:
         if ((active1 & 0x200ULL) != 0L)
         {
            jjmatchedKind = 73;
            jjmatchedPos = 1;
         }
         else if ((active2 & 0x800000ULL) != 0L)
         {
            jjmatchedKind = 151;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0x2000000000000000ULL, active1, 0x20000080006184ULL, active2, 0x80880800603044ULL, active3, 0L);
      case 112:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x4000000000ULL, active2, 0L, active3, 0L);
      case 114:
         if ((active1 & 0x80000000000ULL) != 0L)
         {
            jjmatchedKind = 107;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0x1000000000000000ULL, active1, 0x1240020440180000ULL, active2, 0x1400100c000ULL, active3, 0L);
      case 115:
         if ((active2 & 0x8ULL) != 0L)
         {
            jjmatchedKind = 131;
            jjmatchedPos = 1;
         }
         else if ((active2 & 0x400ULL) != 0L)
         {
            jjmatchedKind = 138;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x2000400000000000ULL, active2, 0x2000200000000ULL, active3, 0L);
      case 116:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x800008ULL, active2, 0x1000000000ULL, active3, 0L);
      case 117:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x18000001200000ULL, active2, 0x11000000000000ULL, active3, 0L);
      case 119:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x2000000ULL, active2, 0L, active3, 0L);
      case 120:
         return jjMoveStringLiteralDfa2_0(active0, 0L, active1, 0x800ULL, active2, 0xa000000000ULL, active3, 0L);
      case 121:
         if ((active1 & 0x400000000000000ULL) != 0L)
         {
            jjmatchedKind = 122;
            jjmatchedPos = 1;
         }
         return jjMoveStringLiteralDfa2_0(active0, 0x4000000000000000ULL, active1, 0x4000000ULL, active2, 0L, active3, 0L);
      case 124:
         if ((active0 & 0x80000000ULL) != 0L)
         {
            jjmatchedKind = 31;
            jjmatchedPos = 1;
         }
         break;
      default :
         break;
   }
   return jjMoveNfa_0(0, 1);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa2_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2, unsigned long long old3, unsigned long long active3){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2) | (active3 &= old3)) == 0L)
      return jjMoveNfa_0(0, 1);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 1);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 62:
         if ((active0 & 0x40000000000000ULL) != 0L)
         {
            jjmatchedKind = 54;
            jjmatchedPos = 2;
         }
         break;
      case 65:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x40001000000020ULL);
      case 66:
         if ((active2 & 0x10000000000000ULL) != 0L)
         {
            jjmatchedKind = 180;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x20000ULL);
      case 67:
         if ((active1 & 0x2000000000000000ULL) != 0L)
         {
            jjmatchedKind = 125;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x400000000000ULL, active2, 0x400000000ULL);
      case 68:
         if ((active1 & 0x100000000000ULL) != 0L)
         {
            jjmatchedKind = 108;
            jjmatchedPos = 2;
         }
         else if ((active2 & 0x80000ULL) != 0L)
         {
            jjmatchedKind = 147;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x1000004000000000ULL, active2, 0x100200000ULL);
      case 69:
         if ((active2 & 0x2000000000000ULL) != 0L)
         {
            jjmatchedKind = 177;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x40000000000ULL, active2, 0x2008004000ULL);
      case 70:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x800000000000ULL, active2, 0x120000040001ULL);
      case 71:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x1000000000000ULL, active2, 0x4000000000800ULL);
      case 73:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x20000000000000ULL, active2, 0x18205000000ULL);
      case 74:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x600000000000ULL);
      case 75:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x200000000000ULL, active2, 0L);
      case 76:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x110009000000000ULL, active2, 0x1000000402000ULL);
      case 77:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x8000000000000000ULL, active2, 0x80000000001000ULL);
      case 78:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x4000000000000ULL, active2, 0x40100000ULL);
      case 79:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x240020000000000ULL, active2, 0x804000008000ULL);
      case 80:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x80000000ULL);
      case 82:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x28080000000000ULL);
      case 83:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x4000002000000000ULL, active2, 0x10ULL);
      case 84:
         if ((active1 & 0x80000000000000ULL) != 0L)
         {
            jjmatchedKind = 119;
            jjmatchedPos = 2;
         }
         else if ((active2 & 0x4ULL) != 0L)
         {
            jjmatchedKind = 130;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0xa010000000000ULL, active2, 0x40030010200ULL);
      case 86:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x800000000000000ULL, active2, 0L);
      case 87:
         if ((active2 & 0x800000000ULL) != 0L)
         {
            jjmatchedKind = 163;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x40ULL);
      case 89:
         if ((active2 & 0x2000000ULL) != 0L)
         {
            jjmatchedKind = 153;
            jjmatchedPos = 2;
         }
         break;
      case 97:
         return jjMoveStringLiteralDfa3_0(active0, 0x8200000000000000ULL, active1, 0x800000ULL, active2, 0x40001000000020ULL);
      case 98:
         if ((active2 & 0x10000000000000ULL) != 0L)
         {
            jjmatchedKind = 180;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x200000ULL, active2, 0x20000ULL);
      case 99:
         if ((active1 & 0x2000000000000000ULL) != 0L)
         {
            jjmatchedKind = 125;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0x100000000000000ULL, active1, 0x400200000000ULL, active2, 0x400000000ULL);
      case 100:
         if ((active1 & 0x100000000000ULL) != 0L)
         {
            jjmatchedKind = 108;
            jjmatchedPos = 2;
         }
         else if ((active2 & 0x80000ULL) != 0L)
         {
            jjmatchedKind = 147;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x1000004000000000ULL, active2, 0x100200000ULL);
      case 101:
         if ((active2 & 0x2000000000000ULL) != 0L)
         {
            jjmatchedKind = 177;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0x1000000000000000ULL, active1, 0x40000000000ULL, active2, 0x2008004000ULL);
      case 102:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x800000000000ULL, active2, 0x120000040001ULL);
      case 103:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x1000000000000ULL, active2, 0x4000000000800ULL);
      case 105:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x2000018a080000ULL, active2, 0x18205000000ULL);
      case 106:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x600000000000ULL);
      case 107:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x200000000000ULL, active2, 0L);
      case 108:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x110009800000000ULL, active2, 0x1000000402000ULL);
      case 109:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x8000000000000000ULL, active2, 0x80000000001000ULL);
      case 110:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x4000004001184ULL, active2, 0x40100000ULL);
      case 111:
         return jjMoveStringLiteralDfa3_0(active0, 0x2000000000000000ULL, active1, 0x240020000100001ULL, active2, 0x804000008000ULL);
      case 112:
         return jjMoveStringLiteralDfa3_0(active0, 0x80000000000000ULL, active1, 0x1010000ULL, active2, 0x80000000ULL);
      case 114:
         if ((active1 & 0x10ULL) != 0L)
         {
            jjmatchedKind = 68;
            jjmatchedPos = 2;
         }
         else if ((active1 & 0x2000ULL) != 0L)
         {
            jjmatchedKind = 77;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x30000008ULL, active2, 0x28080000000000ULL);
      case 115:
         return jjMoveStringLiteralDfa3_0(active0, 0x800000000000000ULL, active1, 0x4000002000020420ULL, active2, 0x10ULL);
      case 116:
         if ((active1 & 0x2ULL) != 0L)
         {
            jjmatchedKind = 65;
            jjmatchedPos = 2;
         }
         else if ((active1 & 0x80000000000000ULL) != 0L)
         {
            jjmatchedKind = 119;
            jjmatchedPos = 2;
         }
         else if ((active2 & 0x4ULL) != 0L)
         {
            jjmatchedKind = 130;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0x4400000000000000ULL, active1, 0xa010000404840ULL, active2, 0x40030010200ULL);
      case 117:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x400000000ULL, active2, 0L);
      case 118:
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0x800000000000000ULL, active2, 0L);
      case 119:
         if ((active1 & 0x40000ULL) != 0L)
         {
            jjmatchedKind = 82;
            jjmatchedPos = 2;
         }
         else if ((active2 & 0x800000000ULL) != 0L)
         {
            jjmatchedKind = 163;
            jjmatchedPos = 2;
         }
         return jjMoveStringLiteralDfa3_0(active0, 0L, active1, 0L, active2, 0x40ULL);
      case 121:
         if ((active1 & 0x40000000ULL) != 0L)
         {
            jjmatchedKind = 94;
            jjmatchedPos = 2;
         }
         else if ((active2 & 0x2000000ULL) != 0L)
         {
            jjmatchedKind = 153;
            jjmatchedPos = 2;
         }
         break;
      default :
         break;
   }
   return jjMoveNfa_0(0, 2);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa3_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 2);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 2);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 65:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x404000000000ULL, active2, 0x144040ULL);
      case 67:
         if ((active1 & 0x4000000000000000ULL) != 0L)
         {
            jjmatchedKind = 126;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x6008000000ULL);
      case 68:
         if ((active2 & 0x40000000000000ULL) != 0L)
         {
            jjmatchedKind = 182;
            jjmatchedPos = 3;
         }
         break;
      case 69:
         if ((active1 & 0x200000000000ULL) != 0L)
         {
            jjmatchedKind = 109;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x100c00b000000000ULL, active2, 0x1c0100010000ULL);
      case 71:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x10040000000ULL);
      case 72:
         if ((active2 & 0x400000000ULL) != 0L)
         {
            jjmatchedKind = 162;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x1000000000000ULL, active2, 0L);
      case 73:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x8800000000000000ULL, active2, 0x24000000200800ULL);
      case 76:
         if ((active1 & 0x10000000000000ULL) != 0L)
         {
            jjmatchedKind = 116;
            jjmatchedPos = 3;
         }
         else if ((active2 & 0x800000000000ULL) != 0L)
         {
            jjmatchedKind = 175;
            jjmatchedPos = 3;
         }
         else if ((active2 & 0x1000000000000ULL) != 0L)
         {
            jjmatchedKind = 176;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x80022000ULL);
      case 77:
         if ((active1 & 0x20000000000ULL) != 0L)
         {
            jjmatchedKind = 105;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x80000001001000ULL);
      case 78:
         if ((active1 & 0x20000000000000ULL) != 0L)
         {
            jjmatchedKind = 117;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x200000000ULL);
      case 79:
         if ((active1 & 0x10000000000ULL) != 0L)
         {
            jjmatchedKind = 104;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x20020000000ULL);
      case 80:
         if ((active2 & 0x8000ULL) != 0L)
         {
            jjmatchedKind = 143;
            jjmatchedPos = 3;
         }
         break;
      case 81:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x4000000ULL);
      case 82:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x40000000000ULL, active2, 0x20ULL);
      case 83:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x40000000000000ULL, active2, 0x8000000001ULL);
      case 84:
         if ((active1 & 0x800000000000ULL) != 0L)
         {
            jjmatchedKind = 111;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x8001000000010ULL);
      case 85:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x302000000000000ULL, active2, 0x600010400000ULL);
      case 87:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x200ULL);
      case 97:
         return jjMoveStringLiteralDfa4_0(active0, 0x1000000000000000ULL, active1, 0x404000001000ULL, active2, 0x144040ULL);
      case 99:
         if ((active1 & 0x4000000000000000ULL) != 0L)
         {
            jjmatchedKind = 126;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x4000040ULL, active2, 0x6008000000ULL);
      case 100:
         if ((active1 & 0x80000000ULL) != 0L)
         {
            jjmatchedKind = 95;
            jjmatchedPos = 3;
         }
         else if ((active2 & 0x40000000000000ULL) != 0L)
         {
            jjmatchedKind = 182;
            jjmatchedPos = 3;
         }
         break;
      case 101:
         if ((active0 & 0x4000000000000000ULL) != 0L)
         {
            jjmatchedKind = 62;
            jjmatchedPos = 3;
         }
         else if ((active1 & 0x20ULL) != 0L)
         {
            jjmatchedKind = 69;
            jjmatchedPos = 3;
         }
         else if ((active1 & 0x400ULL) != 0L)
         {
            jjmatchedKind = 74;
            jjmatchedPos = 3;
         }
         else if ((active1 & 0x400000000ULL) != 0L)
         {
            jjmatchedKind = 98;
            jjmatchedPos = 3;
         }
         else if ((active1 & 0x200000000000ULL) != 0L)
         {
            jjmatchedKind = 109;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0x400000000000000ULL, active1, 0x100c00b001000800ULL, active2, 0x1c0100010000ULL);
      case 103:
         if ((active1 & 0x4ULL) != 0L)
         {
            jjmatchedKind = 66;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x10040000000ULL);
      case 104:
         if ((active2 & 0x400000000ULL) != 0L)
         {
            jjmatchedKind = 162;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x1000000000000ULL, active2, 0L);
      case 105:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x8800000000000008ULL, active2, 0x24000000200800ULL);
      case 107:
         return jjMoveStringLiteralDfa4_0(active0, 0x100000000000000ULL, active1, 0L, active2, 0L);
      case 108:
         if ((active1 & 0x10000000000000ULL) != 0L)
         {
            jjmatchedKind = 116;
            jjmatchedPos = 3;
         }
         else if ((active2 & 0x800000000000ULL) != 0L)
         {
            jjmatchedKind = 175;
            jjmatchedPos = 3;
         }
         else if ((active2 & 0x1000000000000ULL) != 0L)
         {
            jjmatchedKind = 176;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0x2000000000000000ULL, active1, 0x300210000ULL, active2, 0x80022000ULL);
      case 109:
         if ((active1 & 0x20000000000ULL) != 0L)
         {
            jjmatchedKind = 105;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x80000001001000ULL);
      case 110:
         if ((active1 & 0x20000000000000ULL) != 0L)
         {
            jjmatchedKind = 117;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x200000000ULL);
      case 111:
         if ((active1 & 0x4000ULL) != 0L)
         {
            jjmatchedKind = 78;
            jjmatchedPos = 3;
         }
         else if ((active1 & 0x10000000000ULL) != 0L)
         {
            jjmatchedKind = 104;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0x80000000000000ULL, active1, 0x30000000ULL, active2, 0x20020000000ULL);
      case 112:
         if ((active2 & 0x8000ULL) != 0L)
         {
            jjmatchedKind = 143;
            jjmatchedPos = 3;
         }
         break;
      case 113:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x4000000ULL);
      case 114:
         if ((active0 & 0x8000000000000000ULL) != 0L)
         {
            jjmatchedKind = 63;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x40000000001ULL, active2, 0x20ULL);
      case 115:
         if ((active1 & 0x8000000ULL) != 0L)
         {
            jjmatchedKind = 91;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0x200000000000000ULL, active1, 0x40000800000080ULL, active2, 0x8000000001ULL);
      case 116:
         if ((active1 & 0x800000000000ULL) != 0L)
         {
            jjmatchedKind = 111;
            jjmatchedPos = 3;
         }
         return jjMoveStringLiteralDfa4_0(active0, 0x800000000000000ULL, active1, 0x2920100ULL, active2, 0x8001000000010ULL);
      case 117:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x302000000400000ULL, active2, 0x600010400000ULL);
      case 118:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0x80000ULL, active2, 0L);
      case 119:
         return jjMoveStringLiteralDfa4_0(active0, 0L, active1, 0L, active2, 0x200ULL);
      default :
         break;
   }
   return jjMoveNfa_0(0, 3);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa4_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 3);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 3);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 65:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x20000081000000ULL);
      case 66:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x2000ULL);
      case 67:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x1000000000ULL, active2, 0L);
      case 69:
         if ((active1 & 0x40000000000ULL) != 0L)
         {
            jjmatchedKind = 106;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x20ULL) != 0L)
         {
            jjmatchedKind = 133;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x20000ULL) != 0L)
         {
            jjmatchedKind = 145;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x100000000000000ULL, active2, 0x5000000201ULL);
      case 70:
         if ((active2 & 0x20000000ULL) != 0L)
         {
            jjmatchedKind = 157;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x200000ULL);
      case 71:
         if ((active2 & 0x200000000ULL) != 0L)
         {
            jjmatchedKind = 161;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x10000000000ULL);
      case 73:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x88080000001050ULL);
      case 75:
         if ((active2 & 0x8000000ULL) != 0L)
         {
            jjmatchedKind = 155;
            jjmatchedPos = 4;
         }
         break;
      case 77:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x500000ULL);
      case 78:
         if ((active2 & 0x800ULL) != 0L)
         {
            jjmatchedKind = 139;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x800000000000000ULL, active2, 0L);
      case 79:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x4000000000000ULL);
      case 80:
         if ((active1 & 0x200000000000000ULL) != 0L)
         {
            jjmatchedKind = 121;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x400000000000ULL, active2, 0L);
      case 82:
         if ((active1 & 0x4000000000000ULL) != 0L)
         {
            jjmatchedKind = 114;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x8000000000000ULL) != 0L)
         {
            jjmatchedKind = 115;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x1000000000000000ULL) != 0L)
         {
            jjmatchedKind = 124;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x10000ULL) != 0L)
         {
            jjmatchedKind = 144;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x40000000000ULL) != 0L)
         {
            jjmatchedKind = 170;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x2002000000000ULL, active2, 0x120010000000ULL);
      case 83:
         if ((active1 & 0x40000000000000ULL) != 0L)
         {
            jjmatchedKind = 118;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x600000000000ULL);
      case 84:
         if ((active1 & 0x1000000000000ULL) != 0L)
         {
            jjmatchedKind = 112;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x8000000000000000ULL) != 0L)
         {
            jjmatchedKind = 127;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0xc000000000ULL, active2, 0x8000004000ULL);
      case 85:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x2044040000ULL);
      case 88:
         if ((active2 & 0x100000000ULL) != 0L)
         {
            jjmatchedKind = 160;
            jjmatchedPos = 4;
         }
         break;
      case 97:
         return jjMoveStringLiteralDfa5_0(active0, 0x100000000000000ULL, active1, 0xa0000ULL, active2, 0x20000081000000ULL);
      case 98:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x2000ULL);
      case 99:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x1002000000ULL, active2, 0L);
      case 101:
         if ((active1 & 0x100000000ULL) != 0L)
         {
            jjmatchedKind = 96;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x800000000ULL) != 0L)
         {
            jjmatchedKind = 99;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x40000000000ULL) != 0L)
         {
            jjmatchedKind = 106;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x20ULL) != 0L)
         {
            jjmatchedKind = 133;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x20000ULL) != 0L)
         {
            jjmatchedKind = 145;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0x2000000000000000ULL, active1, 0x100000000110000ULL, active2, 0x5000000201ULL);
      case 102:
         if ((active2 & 0x20000000ULL) != 0L)
         {
            jjmatchedKind = 157;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x200000ULL);
      case 103:
         if ((active2 & 0x200000000ULL) != 0L)
         {
            jjmatchedKind = 161;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x10000000000ULL);
      case 104:
         if ((active1 & 0x40ULL) != 0L)
         {
            jjmatchedKind = 70;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x4000000ULL, active2, 0L);
      case 105:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0xa00100ULL, active2, 0x88080000001050ULL);
      case 107:
         if ((active0 & 0x1000000000000000ULL) != 0L)
         {
            jjmatchedKind = 60;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x8000000ULL) != 0L)
         {
            jjmatchedKind = 155;
            jjmatchedPos = 4;
         }
         break;
      case 108:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x1000ULL, active2, 0L);
      case 109:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x500000ULL);
      case 110:
         if ((active2 & 0x800ULL) != 0L)
         {
            jjmatchedKind = 139;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x800000000000808ULL, active2, 0L);
      case 111:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x4000000000000ULL);
      case 112:
         if ((active1 & 0x200000000000000ULL) != 0L)
         {
            jjmatchedKind = 121;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x400000000000ULL, active2, 0L);
      case 114:
         if ((active1 & 0x1000000ULL) != 0L)
         {
            jjmatchedKind = 88;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x4000000000000ULL) != 0L)
         {
            jjmatchedKind = 114;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x8000000000000ULL) != 0L)
         {
            jjmatchedKind = 115;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x1000000000000000ULL) != 0L)
         {
            jjmatchedKind = 124;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x10000ULL) != 0L)
         {
            jjmatchedKind = 144;
            jjmatchedPos = 4;
         }
         else if ((active2 & 0x40000000000ULL) != 0L)
         {
            jjmatchedKind = 170;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0xc80000000000000ULL, active1, 0x2002000400000ULL, active2, 0x120010000000ULL);
      case 115:
         if ((active0 & 0x200000000000000ULL) != 0L)
         {
            jjmatchedKind = 57;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x40000000000000ULL) != 0L)
         {
            jjmatchedKind = 118;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0L, active2, 0x600000000000ULL);
      case 116:
         if ((active1 & 0x1ULL) != 0L)
         {
            jjmatchedKind = 64;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x80ULL) != 0L)
         {
            jjmatchedKind = 71;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x1000000000000ULL) != 0L)
         {
            jjmatchedKind = 112;
            jjmatchedPos = 4;
         }
         else if ((active1 & 0x8000000000000000ULL) != 0L)
         {
            jjmatchedKind = 127;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0xc000000000ULL, active2, 0x8000004000ULL);
      case 117:
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x200000000ULL, active2, 0x2044040000ULL);
      case 119:
         if ((active1 & 0x10000000ULL) != 0L)
         {
            jjmatchedKind = 92;
            jjmatchedPos = 4;
         }
         return jjMoveStringLiteralDfa5_0(active0, 0L, active1, 0x20000000ULL, active2, 0L);
      case 120:
         if ((active2 & 0x100000000ULL) != 0L)
         {
            jjmatchedKind = 160;
            jjmatchedPos = 4;
         }
         break;
      default :
         break;
   }
   return jjMoveNfa_0(0, 4);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa5_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 4);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 4);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 65:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x2000000000000ULL, active2, 0x40002000ULL);
      case 67:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x80000000ULL);
      case 68:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x4000000000ULL);
      case 69:
         if ((active1 & 0x4000000000ULL) != 0L)
         {
            jjmatchedKind = 102;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x8000000000ULL) != 0L)
         {
            jjmatchedKind = 103;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x400000000000ULL) != 0L)
         {
            jjmatchedKind = 110;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x4000ULL) != 0L)
         {
            jjmatchedKind = 142;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x100000ULL) != 0L)
         {
            jjmatchedKind = 148;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x4000000ULL) != 0L)
         {
            jjmatchedKind = 154;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x20000000000ULL) != 0L)
         {
            jjmatchedKind = 169;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x110000000200ULL);
      case 71:
         if ((active1 & 0x800000000000000ULL) != 0L)
         {
            jjmatchedKind = 123;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x80000000000ULL);
      case 76:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x20000000040000ULL);
      case 77:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x1000000000ULL);
      case 78:
         if ((active2 & 0x400000ULL) != 0L)
         {
            jjmatchedKind = 150;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x4000000000000ULL) != 0L)
         {
            jjmatchedKind = 178;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x10000010ULL);
      case 82:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x1000000ULL);
      case 83:
         if ((active1 & 0x100000000000000ULL) != 0L)
         {
            jjmatchedKind = 120;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x8000000000ULL) != 0L)
         {
            jjmatchedKind = 167;
            jjmatchedPos = 5;
         }
         break;
      case 84:
         if ((active1 & 0x1000000000ULL) != 0L)
         {
            jjmatchedKind = 100;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x2000000000ULL) != 0L)
         {
            jjmatchedKind = 101;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x1ULL) != 0L)
         {
            jjmatchedKind = 128;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x40ULL) != 0L)
         {
            jjmatchedKind = 134;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x1000ULL) != 0L)
         {
            jjmatchedKind = 140;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x88602000000000ULL);
      case 89:
         if ((active2 & 0x200000ULL) != 0L)
         {
            jjmatchedKind = 149;
            jjmatchedPos = 5;
         }
         break;
      case 97:
         return jjMoveStringLiteralDfa6_0(active0, 0x2800000000000000ULL, active1, 0x2000000000000ULL, active2, 0x40002000ULL);
      case 99:
         if ((active1 & 0x200000ULL) != 0L)
         {
            jjmatchedKind = 85;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x800000ULL) != 0L)
         {
            jjmatchedKind = 87;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x100000ULL, active2, 0x80000000ULL);
      case 100:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x200000800ULL, active2, 0x4000000000ULL);
      case 101:
         if ((active1 & 0x4000000000ULL) != 0L)
         {
            jjmatchedKind = 102;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x8000000000ULL) != 0L)
         {
            jjmatchedKind = 103;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x400000000000ULL) != 0L)
         {
            jjmatchedKind = 110;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x4000ULL) != 0L)
         {
            jjmatchedKind = 142;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x100000ULL) != 0L)
         {
            jjmatchedKind = 148;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x4000000ULL) != 0L)
         {
            jjmatchedKind = 154;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x20000000000ULL) != 0L)
         {
            jjmatchedKind = 169;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0L, active2, 0x110000000200ULL);
      case 102:
         return jjMoveStringLiteralDfa6_0(active0, 0x400000000000000ULL, active1, 0L, active2, 0L);
      case 103:
         if ((active1 & 0x8ULL) != 0L)
         {
            jjmatchedKind = 67;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x800000000000000ULL) != 0L)
         {
            jjmatchedKind = 123;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0x100000000000000ULL, active1, 0L, active2, 0x80000000000ULL);
      case 104:
         if ((active1 & 0x2000000ULL) != 0L)
         {
            jjmatchedKind = 89;
            jjmatchedPos = 5;
         }
         break;
      case 108:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x1000ULL, active2, 0x20000000040000ULL);
      case 109:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x10000ULL, active2, 0x1000000000ULL);
      case 110:
         if ((active1 & 0x400000ULL) != 0L)
         {
            jjmatchedKind = 86;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x400000ULL) != 0L)
         {
            jjmatchedKind = 150;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x4000000000000ULL) != 0L)
         {
            jjmatchedKind = 178;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x20100ULL, active2, 0x10000010ULL);
      case 114:
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x4000000ULL, active2, 0x1000000ULL);
      case 115:
         if ((active1 & 0x20000000ULL) != 0L)
         {
            jjmatchedKind = 93;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x100000000000000ULL) != 0L)
         {
            jjmatchedKind = 120;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x8000000000ULL) != 0L)
         {
            jjmatchedKind = 167;
            jjmatchedPos = 5;
         }
         break;
      case 116:
         if ((active0 & 0x80000000000000ULL) != 0L)
         {
            jjmatchedKind = 55;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x1000000000ULL) != 0L)
         {
            jjmatchedKind = 100;
            jjmatchedPos = 5;
         }
         else if ((active1 & 0x2000000000ULL) != 0L)
         {
            jjmatchedKind = 101;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x1ULL) != 0L)
         {
            jjmatchedKind = 128;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x40ULL) != 0L)
         {
            jjmatchedKind = 134;
            jjmatchedPos = 5;
         }
         else if ((active2 & 0x1000ULL) != 0L)
         {
            jjmatchedKind = 140;
            jjmatchedPos = 5;
         }
         return jjMoveStringLiteralDfa6_0(active0, 0L, active1, 0x80000ULL, active2, 0x88602000000000ULL);
      case 121:
         if ((active2 & 0x200000ULL) != 0L)
         {
            jjmatchedKind = 149;
            jjmatchedPos = 5;
         }
         break;
      default :
         break;
   }
   return jjMoveNfa_0(0, 5);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa6_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 5);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 5);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 67:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x2010ULL);
      case 69:
         if ((active2 & 0x80000000ULL) != 0L)
         {
            jjmatchedKind = 159;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x2000000000ULL) != 0L)
         {
            jjmatchedKind = 165;
            jjmatchedPos = 6;
         }
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x1000000000ULL);
      case 71:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x40000000ULL);
      case 73:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x28000000000000ULL);
      case 76:
         if ((active1 & 0x2000000000000ULL) != 0L)
         {
            jjmatchedKind = 113;
            jjmatchedPos = 6;
         }
         break;
      case 78:
         if ((active2 & 0x200ULL) != 0L)
         {
            jjmatchedKind = 137;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x80000000000ULL) != 0L)
         {
            jjmatchedKind = 171;
            jjmatchedPos = 6;
         }
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x100000000000ULL);
      case 82:
         if ((active2 & 0x10000000000ULL) != 0L)
         {
            jjmatchedKind = 168;
            jjmatchedPos = 6;
         }
         break;
      case 83:
         if ((active2 & 0x10000000ULL) != 0L)
         {
            jjmatchedKind = 156;
            jjmatchedPos = 6;
         }
         break;
      case 84:
         if ((active2 & 0x40000ULL) != 0L)
         {
            jjmatchedKind = 146;
            jjmatchedPos = 6;
         }
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x80000000000000ULL);
      case 85:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x4000000000ULL);
      case 89:
         if ((active2 & 0x1000000ULL) != 0L)
         {
            jjmatchedKind = 152;
            jjmatchedPos = 6;
         }
         break;
      case 95:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x600000000000ULL);
      case 97:
         return jjMoveStringLiteralDfa7_0(active0, 0x400000000000000ULL, active1, 0L, active2, 0L);
      case 99:
         return jjMoveStringLiteralDfa7_0(active0, 0x800000000000000ULL, active1, 0x20000ULL, active2, 0x2010ULL);
      case 101:
         if ((active0 & 0x100000000000000ULL) != 0L)
         {
            jjmatchedKind = 56;
            jjmatchedPos = 6;
         }
         else if ((active1 & 0x80000ULL) != 0L)
         {
            jjmatchedKind = 83;
            jjmatchedPos = 6;
         }
         else if ((active1 & 0x200000000ULL) != 0L)
         {
            jjmatchedKind = 97;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x80000000ULL) != 0L)
         {
            jjmatchedKind = 159;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x2000000000ULL) != 0L)
         {
            jjmatchedKind = 165;
            jjmatchedPos = 6;
         }
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0x10000ULL, active2, 0x1000000000ULL);
      case 103:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x40000000ULL);
      case 105:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x28000000000000ULL);
      case 108:
         if ((active1 & 0x2000000000000ULL) != 0L)
         {
            jjmatchedKind = 113;
            jjmatchedPos = 6;
         }
         break;
      case 110:
         if ((active0 & 0x2000000000000000ULL) != 0L)
         {
            jjmatchedKind = 61;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x200ULL) != 0L)
         {
            jjmatchedKind = 137;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x80000000000ULL) != 0L)
         {
            jjmatchedKind = 171;
            jjmatchedPos = 6;
         }
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0L, active2, 0x100000000000ULL);
      case 111:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0x4000000ULL, active2, 0L);
      case 114:
         if ((active2 & 0x10000000000ULL) != 0L)
         {
            jjmatchedKind = 168;
            jjmatchedPos = 6;
         }
         break;
      case 115:
         if ((active1 & 0x800ULL) != 0L)
         {
            jjmatchedKind = 75;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x10000000ULL) != 0L)
         {
            jjmatchedKind = 156;
            jjmatchedPos = 6;
         }
         break;
      case 116:
         if ((active2 & 0x40000ULL) != 0L)
         {
            jjmatchedKind = 146;
            jjmatchedPos = 6;
         }
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0x100000ULL, active2, 0x80000000000000ULL);
      case 117:
         return jjMoveStringLiteralDfa7_0(active0, 0L, active1, 0x100ULL, active2, 0x4000000000ULL);
      case 121:
         if ((active1 & 0x1000ULL) != 0L)
         {
            jjmatchedKind = 76;
            jjmatchedPos = 6;
         }
         else if ((active2 & 0x1000000ULL) != 0L)
         {
            jjmatchedKind = 152;
            jjmatchedPos = 6;
         }
         break;
      default :
         break;
   }
   return jjMoveNfa_0(0, 6);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa7_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 6);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 6);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 67:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x100000000000ULL);
      case 69:
         if ((active2 & 0x40000000ULL) != 0L)
         {
            jjmatchedKind = 158;
            jjmatchedPos = 7;
         }
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x80000000000000ULL);
      case 75:
         if ((active2 & 0x2000ULL) != 0L)
         {
            jjmatchedKind = 141;
            jjmatchedPos = 7;
         }
         break;
      case 78:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x1000000000ULL);
      case 79:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x8000000000000ULL);
      case 82:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x4000000000ULL);
      case 83:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x400000000000ULL);
      case 84:
         if ((active2 & 0x10ULL) != 0L)
         {
            jjmatchedKind = 132;
            jjmatchedPos = 7;
         }
         break;
      case 87:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x200000000000ULL);
      case 90:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x20000000000000ULL);
      case 99:
         return jjMoveStringLiteralDfa8_0(active0, 0x400000000000000ULL, active1, 0L, active2, 0x100000000000ULL);
      case 101:
         if ((active1 & 0x100ULL) != 0L)
         {
            jjmatchedKind = 72;
            jjmatchedPos = 7;
         }
         else if ((active2 & 0x40000000ULL) != 0L)
         {
            jjmatchedKind = 158;
            jjmatchedPos = 7;
         }
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0x120000ULL, active2, 0x80000000000000ULL);
      case 107:
         if ((active2 & 0x2000ULL) != 0L)
         {
            jjmatchedKind = 141;
            jjmatchedPos = 7;
         }
         break;
      case 110:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0x4010000ULL, active2, 0x1000000000ULL);
      case 111:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x8000000000000ULL);
      case 114:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x4000000000ULL);
      case 115:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x400000000000ULL);
      case 116:
         if ((active0 & 0x800000000000000ULL) != 0L)
         {
            jjmatchedKind = 59;
            jjmatchedPos = 7;
         }
         else if ((active2 & 0x10ULL) != 0L)
         {
            jjmatchedKind = 132;
            jjmatchedPos = 7;
         }
         break;
      case 119:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x200000000000ULL);
      case 122:
         return jjMoveStringLiteralDfa8_0(active0, 0L, active1, 0L, active2, 0x20000000000000ULL);
      default :
         break;
   }
   return jjMoveNfa_0(0, 7);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa8_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 7);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 7);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 65:
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0L, active2, 0x20000000000000ULL);
      case 68:
         if ((active2 & 0x80000000000000ULL) != 0L)
         {
            jjmatchedKind = 183;
            jjmatchedPos = 8;
         }
         break;
      case 69:
         if ((active2 & 0x4000000000ULL) != 0L)
         {
            jjmatchedKind = 166;
            jjmatchedPos = 8;
         }
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0L, active2, 0x500000000000ULL);
      case 72:
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0L, active2, 0x200000000000ULL);
      case 78:
         if ((active2 & 0x8000000000000ULL) != 0L)
         {
            jjmatchedKind = 179;
            jjmatchedPos = 8;
         }
         break;
      case 84:
         if ((active2 & 0x1000000000ULL) != 0L)
         {
            jjmatchedKind = 164;
            jjmatchedPos = 8;
         }
         break;
      case 97:
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0L, active2, 0x20000000000000ULL);
      case 100:
         if ((active1 & 0x100000ULL) != 0L)
         {
            jjmatchedKind = 84;
            jjmatchedPos = 8;
         }
         else if ((active2 & 0x80000000000000ULL) != 0L)
         {
            jjmatchedKind = 183;
            jjmatchedPos = 8;
         }
         break;
      case 101:
         if ((active0 & 0x400000000000000ULL) != 0L)
         {
            jjmatchedKind = 58;
            jjmatchedPos = 8;
         }
         else if ((active2 & 0x4000000000ULL) != 0L)
         {
            jjmatchedKind = 166;
            jjmatchedPos = 8;
         }
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0L, active2, 0x500000000000ULL);
      case 104:
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0L, active2, 0x200000000000ULL);
      case 105:
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0x4000000ULL, active2, 0L);
      case 110:
         if ((active2 & 0x8000000000000ULL) != 0L)
         {
            jjmatchedKind = 179;
            jjmatchedPos = 8;
         }
         break;
      case 111:
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0x20000ULL, active2, 0L);
      case 116:
         if ((active2 & 0x1000000000ULL) != 0L)
         {
            jjmatchedKind = 164;
            jjmatchedPos = 8;
         }
         return jjMoveStringLiteralDfa9_0(active0, 0L, active1, 0x10000ULL, active2, 0L);
      default :
         break;
   }
   return jjMoveNfa_0(0, 8);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa9_0(unsigned long long old0, unsigned long long active0, unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active0 &= old0) | (active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 8);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 8);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 66:
         return jjMoveStringLiteralDfa10_0(active1, 0L, active2, 0x20000000000000ULL);
      case 69:
         return jjMoveStringLiteralDfa10_0(active1, 0L, active2, 0x200000000000ULL);
      case 83:
         if ((active2 & 0x100000000000ULL) != 0L)
         {
            jjmatchedKind = 172;
            jjmatchedPos = 9;
         }
         break;
      case 84:
         if ((active2 & 0x400000000000ULL) != 0L)
         {
            jjmatchedKind = 174;
            jjmatchedPos = 9;
         }
         break;
      case 98:
         return jjMoveStringLiteralDfa10_0(active1, 0L, active2, 0x20000000000000ULL);
      case 101:
         return jjMoveStringLiteralDfa10_0(active1, 0L, active2, 0x200000000000ULL);
      case 102:
         if ((active1 & 0x20000ULL) != 0L)
         {
            jjmatchedKind = 81;
            jjmatchedPos = 9;
         }
         break;
      case 115:
         if ((active1 & 0x10000ULL) != 0L)
         {
            jjmatchedKind = 80;
            jjmatchedPos = 9;
         }
         else if ((active2 & 0x100000000000ULL) != 0L)
         {
            jjmatchedKind = 172;
            jjmatchedPos = 9;
         }
         break;
      case 116:
         if ((active2 & 0x400000000000ULL) != 0L)
         {
            jjmatchedKind = 174;
            jjmatchedPos = 9;
         }
         break;
      case 122:
         return jjMoveStringLiteralDfa10_0(active1, 0x4000000ULL, active2, 0L);
      default :
         break;
   }
   return jjMoveNfa_0(0, 9);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa10_0(unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 9);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 9);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 76:
         return jjMoveStringLiteralDfa11_0(active1, 0L, active2, 0x20000000000000ULL);
      case 82:
         return jjMoveStringLiteralDfa11_0(active1, 0L, active2, 0x200000000000ULL);
      case 101:
         return jjMoveStringLiteralDfa11_0(active1, 0x4000000ULL, active2, 0L);
      case 108:
         return jjMoveStringLiteralDfa11_0(active1, 0L, active2, 0x20000000000000ULL);
      case 114:
         return jjMoveStringLiteralDfa11_0(active1, 0L, active2, 0x200000000000ULL);
      default :
         break;
   }
   return jjMoveNfa_0(0, 10);
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa11_0(unsigned long long old1, unsigned long long active1, unsigned long long old2, unsigned long long active2){
   if (((active1 &= old1) | (active2 &= old2)) == 0L)
      return jjMoveNfa_0(0, 10);
   if (input_stream->endOfInput()) {
   return jjMoveNfa_0(0, 10);
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 69:
         if ((active2 & 0x200000000000ULL) != 0L)
         {
            jjmatchedKind = 173;
            jjmatchedPos = 11;
         }
         else if ((active2 & 0x20000000000000ULL) != 0L)
         {
            jjmatchedKind = 181;
            jjmatchedPos = 11;
         }
         break;
      case 100:
         if ((active1 & 0x4000000ULL) != 0L)
         {
            jjmatchedKind = 90;
            jjmatchedPos = 11;
         }
         break;
      case 101:
         if ((active2 & 0x200000000000ULL) != 0L)
         {
            jjmatchedKind = 173;
            jjmatchedPos = 11;
         }
         else if ((active2 & 0x20000000000000ULL) != 0L)
         {
            jjmatchedKind = 181;
            jjmatchedPos = 11;
         }
         break;
      default :
         break;
   }
   return jjMoveNfa_0(0, 11);
}

int AlinousLangTokenManager::jjMoveNfa_0(int startState, int curPos){
   int strKind = jjmatchedKind;
   int strPos = jjmatchedPos;
   int seenUpto;
   input_stream->backup(seenUpto = curPos + 1);
   assert(!input_stream->endOfInput());
   curChar = input_stream->readChar();
   curPos = 0;
   int startsAt = 0;
   jjnewStateCnt = 75;
   int i = 1;
   jjstateSet[0] = startState;
   int kind = 0x7fffffff;
   for (;;)
   {
      if (++jjround == 0x7fffffff)
         ReInitRounds();
      if (curChar < 64)
      {
         unsigned long long l = 1ULL << curChar;
         (void)l;
         do
         {
            switch(jjstateSet[--i])
            {
               case 0:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(0, 6); }
                  else if (curChar == 39)
                     { jjCheckNAddStates(7, 11); }
                  else if (curChar == 34)
                     { jjCheckNAddStates(12, 14); }
                  else if (curChar == 46)
                     { jjCheckNAdd(9); }
                  else if (curChar == 45)
                     { jjAddStates(15, 16); }
                  if ((0x3fe000000000000ULL & l) != 0L)
                  {
                     if (kind > 9)
                        kind = 9;
                     { jjCheckNAddTwoStates(2, 3); }
                  }
                  else if (curChar == 48)
                  {
                     if (kind > 9)
                        kind = 9;
                     { jjCheckNAddStates(17, 21); }
                  }
                  break;
               case 1:
                  if ((0x3fe000000000000ULL & l) == 0L)
                     break;
                  if (kind > 9)
                     kind = 9;
                  { jjCheckNAddTwoStates(2, 3); }
                  break;
               case 2:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 9)
                     kind = 9;
                  { jjCheckNAddTwoStates(2, 3); }
                  break;
               case 4:
                  if (curChar != 48)
                     break;
                  if (kind > 9)
                     kind = 9;
                  { jjCheckNAddStates(22, 24); }
                  break;
               case 6:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 9)
                     kind = 9;
                  { jjCheckNAddTwoStates(6, 3); }
                  break;
               case 7:
                  if ((0xff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 9)
                     kind = 9;
                  { jjCheckNAddTwoStates(7, 3); }
                  break;
               case 8:
                  if (curChar == 46)
                     { jjCheckNAdd(9); }
                  break;
               case 9:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddStates(25, 27); }
                  break;
               case 11:
                  if ((0x280000000000ULL & l) != 0L)
                     { jjCheckNAdd(12); }
                  break;
               case 12:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddTwoStates(12, 13); }
                  break;
               case 14:
                  if (curChar == 34)
                     { jjCheckNAddStates(12, 14); }
                  break;
               case 15:
                  if ((0xfffffffbffffdbffULL & l) != 0L)
                     { jjCheckNAddStates(12, 14); }
                  break;
               case 17:
                  if ((0x8400000000ULL & l) != 0L)
                     { jjCheckNAddStates(12, 14); }
                  break;
               case 18:
                  if (curChar == 34 && kind > 18)
                     kind = 18;
                  break;
               case 19:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(28, 31); }
                  break;
               case 20:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(12, 14); }
                  break;
               case 21:
                  if ((0xf000000000000ULL & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 22;
                  break;
               case 22:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAdd(20); }
                  break;
               case 24:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 184)
                     kind = 184;
                  jjstateSet[jjnewStateCnt++] = 24;
                  break;
               case 25:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(0, 6); }
                  break;
               case 26:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(32, 34); }
                  break;
               case 28:
                  if ((0x280000000000ULL & l) != 0L)
                     { jjCheckNAdd(29); }
                  break;
               case 29:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(29, 13); }
                  break;
               case 30:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(30, 31); }
                  break;
               case 32:
                  if ((0x280000000000ULL & l) != 0L)
                     { jjCheckNAdd(33); }
                  break;
               case 33:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddTwoStates(33, 13); }
                  break;
               case 34:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(34, 35); }
                  break;
               case 35:
                  if (curChar != 46)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddStates(35, 37); }
                  break;
               case 36:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddStates(35, 37); }
                  break;
               case 38:
                  if ((0x280000000000ULL & l) != 0L)
                     { jjCheckNAdd(39); }
                  break;
               case 39:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddTwoStates(39, 13); }
                  break;
               case 40:
                  if (curChar == 39)
                     { jjCheckNAddStates(7, 11); }
                  break;
               case 41:
                  if ((0xffffff7fffffdbffULL & l) != 0L)
                     { jjCheckNAdd(42); }
                  break;
               case 42:
                  if (curChar == 39 && kind > 19)
                     kind = 19;
                  break;
               case 44:
                  if ((0x8400000000ULL & l) != 0L)
                     { jjCheckNAdd(42); }
                  break;
               case 45:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(46, 42); }
                  break;
               case 46:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAdd(42); }
                  break;
               case 47:
                  if ((0xf000000000000ULL & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 48;
                  break;
               case 48:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAdd(46); }
                  break;
               case 50:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(50, 42); }
                  break;
               case 51:
                  if ((0xffffff7fffffdbffULL & l) != 0L)
                     { jjCheckNAddStates(38, 40); }
                  break;
               case 53:
                  if ((0x8400000000ULL & l) != 0L)
                     { jjCheckNAddStates(38, 40); }
                  break;
               case 54:
                  if (curChar == 39 && kind > 20)
                     kind = 20;
                  break;
               case 55:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(41, 44); }
                  break;
               case 56:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(38, 40); }
                  break;
               case 57:
                  if ((0xf000000000000ULL & l) != 0L)
                     jjstateSet[jjnewStateCnt++] = 58;
                  break;
               case 58:
                  if ((0xff000000000000ULL & l) != 0L)
                     { jjCheckNAdd(56); }
                  break;
               case 60:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(45, 48); }
                  break;
               case 61:
                  if (curChar != 48)
                     break;
                  if (kind > 9)
                     kind = 9;
                  { jjCheckNAddStates(17, 21); }
                  break;
               case 63:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjAddStates(49, 50); }
                  break;
               case 64:
                  if (curChar == 46)
                     { jjCheckNAdd(65); }
                  break;
               case 65:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(65, 66); }
                  break;
               case 67:
                  if ((0x280000000000ULL & l) != 0L)
                     { jjCheckNAdd(68); }
                  break;
               case 68:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddTwoStates(68, 13); }
                  break;
               case 70:
                  if ((0x3ff000000000000ULL & l) != 0L)
                     { jjCheckNAddStates(51, 53); }
                  break;
               case 71:
                  if (curChar == 46)
                     { jjCheckNAdd(72); }
                  break;
               case 73:
                  if ((0x280000000000ULL & l) != 0L)
                     { jjCheckNAdd(74); }
                  break;
               case 74:
                  if ((0x3ff000000000000ULL & l) == 0L)
                     break;
                  if (kind > 13)
                     kind = 13;
                  { jjCheckNAddTwoStates(74, 13); }
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else if (curChar < 128)
      {
         unsigned long long l = 1ULL << (curChar & 077);
         (void)l;
         do
         {
            switch(jjstateSet[--i])
            {
               case 0:
               case 24:
                  if ((0x7fffffe87fffffeULL & l) == 0L)
                     break;
                  if (kind > 184)
                     kind = 184;
                  { jjCheckNAdd(24); }
                  break;
               case 3:
                  if ((0x100000001000ULL & l) != 0L && kind > 9)
                     kind = 9;
                  break;
               case 5:
                  if ((0x100000001000000ULL & l) != 0L)
                     { jjCheckNAdd(6); }
                  break;
               case 6:
                  if ((0x7e0000007eULL & l) == 0L)
                     break;
                  if (kind > 9)
                     kind = 9;
                  { jjCheckNAddTwoStates(6, 3); }
                  break;
               case 10:
                  if ((0x2000000020ULL & l) != 0L)
                     { jjAddStates(54, 55); }
                  break;
               case 13:
                  if ((0x5000000050ULL & l) != 0L && kind > 13)
                     kind = 13;
                  break;
               case 15:
                  if ((0xffffffffefffffffULL & l) != 0L)
                     { jjCheckNAddStates(12, 14); }
                  break;
               case 16:
                  if (curChar == 92)
                     { jjAddStates(56, 58); }
                  break;
               case 17:
                  if ((0x14404410000000ULL & l) != 0L)
                     { jjCheckNAddStates(12, 14); }
                  break;
               case 27:
                  if ((0x2000000020ULL & l) != 0L)
                     { jjAddStates(59, 60); }
                  break;
               case 31:
                  if ((0x2000000020ULL & l) != 0L)
                     { jjAddStates(61, 62); }
                  break;
               case 37:
                  if ((0x2000000020ULL & l) != 0L)
                     { jjAddStates(63, 64); }
                  break;
               case 41:
                  if ((0xffffffffefffffffULL & l) != 0L)
                     { jjCheckNAdd(42); }
                  break;
               case 43:
                  if (curChar == 92)
                     { jjAddStates(65, 68); }
                  break;
               case 44:
                  if ((0x14404410000000ULL & l) != 0L)
                     { jjCheckNAdd(42); }
                  break;
               case 49:
                  if (curChar == 117)
                     { jjCheckNAdd(50); }
                  break;
               case 50:
                  if ((0x7e0000007eULL & l) != 0L)
                     { jjCheckNAddTwoStates(50, 42); }
                  break;
               case 51:
                  if ((0xffffffffefffffffULL & l) != 0L)
                     { jjCheckNAddStates(38, 40); }
                  break;
               case 52:
                  if (curChar == 92)
                     { jjAddStates(69, 72); }
                  break;
               case 53:
                  if ((0x14404410000000ULL & l) != 0L)
                     { jjCheckNAddStates(38, 40); }
                  break;
               case 59:
                  if (curChar == 117)
                     { jjCheckNAdd(60); }
                  break;
               case 60:
                  if ((0x7e0000007eULL & l) != 0L)
                     { jjCheckNAddStates(45, 48); }
                  break;
               case 62:
                  if ((0x100000001000000ULL & l) != 0L)
                     { jjCheckNAddTwoStates(63, 64); }
                  break;
               case 63:
                  if ((0x7e0000007eULL & l) != 0L)
                     { jjCheckNAddTwoStates(63, 64); }
                  break;
               case 65:
                  if ((0x7e0000007eULL & l) != 0L)
                     { jjAddStates(73, 74); }
                  break;
               case 66:
                  if ((0x1000000010000ULL & l) != 0L)
                     { jjAddStates(75, 76); }
                  break;
               case 69:
                  if ((0x100000001000000ULL & l) != 0L)
                     { jjCheckNAdd(70); }
                  break;
               case 70:
                  if ((0x7e0000007eULL & l) != 0L)
                     { jjCheckNAddStates(51, 53); }
                  break;
               case 72:
                  if ((0x1000000010000ULL & l) != 0L)
                     { jjAddStates(77, 78); }
                  break;
               default : break;
            }
         } while(i != startsAt);
      }
      else
      {
         int hiByte = (curChar >> 8);
         int i1 = hiByte >> 6;
         unsigned long long l1 = 1ULL << (hiByte & 077);
         int i2 = (curChar & 0xff) >> 6;
         unsigned long long l2 = 1ULL << (curChar & 077);
         do
         {
            switch(jjstateSet[--i])
            {
               case 15:
                  if (jjCanMove_0(hiByte, i1, i2, l1, l2))
                     { jjAddStates(12, 14); }
                  break;
               case 41:
                  if (jjCanMove_0(hiByte, i1, i2, l1, l2))
                     jjstateSet[jjnewStateCnt++] = 42;
                  break;
               case 51:
                  if (jjCanMove_0(hiByte, i1, i2, l1, l2))
                     { jjAddStates(38, 40); }
                  break;
               default : if (i1 == 0 || l1 == 0 || i2 == 0 ||  l2 == 0) break; else break;
            }
         } while(i != startsAt);
      }
      if (kind != 0x7fffffff)
      {
         jjmatchedKind = kind;
         jjmatchedPos = curPos;
         kind = 0x7fffffff;
      }
      ++curPos;
      if ((i = jjnewStateCnt), (jjnewStateCnt = startsAt), (i == (startsAt = 75 - startsAt)))
         break;
      if (input_stream->endOfInput()) { break; }
      curChar = input_stream->readChar();
   }
   if (jjmatchedPos > strPos)
      return curPos;

   int toRet = MAX(curPos, seenUpto);

   if (curPos < toRet)
      for (i = toRet - MIN(curPos, seenUpto); i-- > 0; )
        {  assert(!input_stream->endOfInput());
           curChar = input_stream->readChar(); }

   if (jjmatchedPos < strPos)
   {
      jjmatchedKind = strKind;
      jjmatchedPos = strPos;
   }
   else if (jjmatchedPos == strPos && jjmatchedKind > strKind)
      jjmatchedKind = strKind;

   return toRet;
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa0_1(){
   switch(curChar)
   {
      case 42:
         return jjMoveStringLiteralDfa1_1(0x2000000000000000ULL);
      default :
         return 1;
   }
}

 int  AlinousLangTokenManager::jjMoveStringLiteralDfa1_1(unsigned long long active2){
   if (input_stream->endOfInput()) {
      return 1;
   }
   curChar = input_stream->readChar();
   switch(curChar)
   {
      case 47:
         if ((active2 & 0x2000000000000000ULL) != 0L)
            return jjStopAtPos(1, 189);
         break;
      default :
         return 2;
   }
   return 2;
}

bool AlinousLangTokenManager::jjCanMove_0(int hiByte, int i1, int i2, unsigned long long l1, unsigned long long l2){
   switch(hiByte)
   {
      case 0:
         return ((jjbitVec2[i2] & l2) != 0L);
      default :
         if ((jjbitVec0[i1] & l1) != 0L)
            return true;
         return false;
   }
}

/** Token literal values. */

Token * AlinousLangTokenManager::jjFillToken(){
   Token *t;
   JJString curTokenImage;
   int beginLine   = -1;
   int endLine     = -1;
   int beginColumn = -1;
   int endColumn   = -1;
   JJString im = jjstrLiteralImages[jjmatchedKind];
   curTokenImage = (im.length() == 0) ? input_stream->GetImage() : im;
   if (input_stream->getTrackLineColumn()) {
     beginLine = input_stream->getBeginLine();
     beginColumn = input_stream->getBeginColumn();
     endLine = input_stream->getEndLine();
     endColumn = input_stream->getEndColumn();
   }
   t = Token::newToken(jjmatchedKind);
   t->kind = jjmatchedKind;
   t->image = curTokenImage;
   t->specialToken = nullptr;
   t->next = nullptr;

   if (input_stream->getTrackLineColumn()) {
   t->beginLine = beginLine;
   t->endLine = endLine;
   t->beginColumn = beginColumn;
   t->endColumn = endColumn;
   }

   return t;
}
const int defaultLexState = 0;
/** Get the next Token. */

Token * AlinousLangTokenManager::getNextToken(){
  Token *specialToken = nullptr;
  Token *matchedToken = nullptr;
  int curPos = 0;

  for (;;)
  {
   EOFLoop: 
   if (input_stream->endOfInput())
   {
      jjmatchedKind = 0;
      jjmatchedPos = -1;
      matchedToken = jjFillToken();
      matchedToken->specialToken = specialToken;
      return matchedToken;
   }
   curChar = input_stream->BeginToken();
   image = jjimage;
   image.clear();
   jjimageLen = 0;

   for (;;)
   {
     switch(curLexState)
     {
       case 0:
         jjmatchedKind = 0x7fffffff;
         jjmatchedPos = 0;
         curPos = jjMoveStringLiteralDfa0_0();
         break;
       case 1:
         jjmatchedKind = 0x7fffffff;
         jjmatchedPos = 0;
         curPos = jjMoveStringLiteralDfa0_1();
         if (jjmatchedPos == 0 && jjmatchedKind > 190)
         {
            jjmatchedKind = 190;
         }
         break;
       case 2:
         jjmatchedKind = 0x7fffffff;
         jjmatchedPos = 0;
         curPos = jjMoveStringLiteralDfa0_2();
         if (jjmatchedPos == 0 && jjmatchedKind > 188)
         {
            jjmatchedKind = 188;
         }
         break;
     }
     if (jjmatchedKind != 0x7fffffff)
     {
        if (jjmatchedPos + 1 < curPos)
           input_stream->backup(curPos - jjmatchedPos - 1);
        if ((jjtoToken[jjmatchedKind >> 6] & (1ULL << (jjmatchedKind & 077))) != 0L)
        {
           matchedToken = jjFillToken();
           matchedToken->specialToken = specialToken;
       if (jjnewLexState[jjmatchedKind] != -1)
         curLexState = jjnewLexState[jjmatchedKind];
           return matchedToken;
        }
        else if ((jjtoSkip[jjmatchedKind >> 6] & (1ULL << (jjmatchedKind & 077))) != 0L)
        {
           if ((jjtoSpecial[jjmatchedKind >> 6] & (1ULL << (jjmatchedKind & 077))) != 0L)
           {
              matchedToken = jjFillToken();
              if (specialToken == nullptr)
                 specialToken = matchedToken;
              else
              {
                 matchedToken->specialToken = specialToken;
                 specialToken = (specialToken->next = matchedToken);
              }
              SkipLexicalActions(matchedToken);
           }
           else
              SkipLexicalActions(nullptr);
         if (jjnewLexState[jjmatchedKind] != -1)
           curLexState = jjnewLexState[jjmatchedKind];
           goto EOFLoop;
        }
        jjimageLen += jjmatchedPos + 1;
      if (jjnewLexState[jjmatchedKind] != -1)
        curLexState = jjnewLexState[jjmatchedKind];
        curPos = 0;
        jjmatchedKind = 0x7fffffff;
     if (!input_stream->endOfInput()) {
           curChar = input_stream->readChar();
     continue;
   }
     }
     int error_line = input_stream->getEndLine();
     int error_column = input_stream->getEndColumn();
     JJString error_after;
     bool EOFSeen = false;
     if (input_stream->endOfInput()) {
        EOFSeen = true;
        error_after = curPos <= 1 ? EMPTY : input_stream->GetImage();
        if (curChar == '\n' || curChar == '\r') {
           error_line++;
           error_column = 0;
        }
        else
           error_column++;
     }
     if (!EOFSeen) {
        error_after = curPos <= 1 ? EMPTY : input_stream->GetImage();
     }
     errorHandler->lexicalError(EOFSeen, curLexState, error_line, error_column, error_after, curChar, this);
   }
  }
}


void  AlinousLangTokenManager::SkipLexicalActions(Token *matchedToken){
   switch(jjmatchedKind)
   {
      default :
         break;
   }
}
  /** Reinitialise parser. */
  void AlinousLangTokenManager::ReInit(JAVACC_CHARSTREAM *stream, int lexState) {
    clear();
    jjmatchedPos = jjnewStateCnt = 0;
    curLexState = lexState;
    input_stream = stream;
    ReInitRounds();
    debugStream = stdout; // init
    SwitchTo(lexState);
    errorHandler = new TokenManagerErrorHandler();
  }

  void AlinousLangTokenManager::ReInitRounds() {
    int i;
    jjround = 0x80000001;
    for (i = 75; i-- > 0;)
      jjrounds[i] = 0x80000000;
  }

  /** Switch to specified lex state. */
  void AlinousLangTokenManager::SwitchTo(int lexState) {
    if (lexState >= 3 || lexState < 0) {
      JJString message;
#ifdef WIDE_CHAR
      message += L"Error: Ignoring invalid lexical state : ";
      message += lexState; message += L". State unchanged.";
#else
      message += "Error: Ignoring invalid lexical state : ";
      message += lexState; message += ". State unchanged.";
#endif
      throw new TokenMgrError(message, INVALID_LEXICAL_STATE);
    } else
      curLexState = lexState;
  }

  /** Constructor. */
  AlinousLangTokenManager::AlinousLangTokenManager (JAVACC_CHARSTREAM *stream, int lexState)
  {
    input_stream = nullptr;
    ReInit(stream, lexState);
  }

  // Destructor
  AlinousLangTokenManager::~AlinousLangTokenManager () {
    clear();
  }

  // clear
  void AlinousLangTokenManager::clear() {
    //Since input_stream was generated outside of TokenManager
    //TokenManager should not take care of deleting it
    //if (input_stream) delete input_stream;
    if (errorHandler) delete errorHandler, errorHandler = nullptr;    
  }


}
