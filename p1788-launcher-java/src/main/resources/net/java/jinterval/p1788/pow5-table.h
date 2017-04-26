/*
   Copyright (C) 2013 JInterval Project.

   This file was generated automatically, don't edit.

   The JInterval C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   In addition to the permissions in the GNU Lesser General Public
   License, the Free Software Foundation gives you unlimited
   permission to link the compiled version of this file into
   combinations with other programs, and to distribute those
   combinations without any restriction coming from the use of this
   file.  (The Lesser General Public License restrictions do apply in
   other respects; for example, they cover modification of the file,
   and distribution when not linked into a combine executable.)

   The JInterval C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the JInterval C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

static UWtype pow5_bits_0[] = {
    0x8000000000000000ull,
};
static UWtype pow5_bits_1[] = {
    0xa000000000000000ull,
};
static UWtype pow5_bits_2[] = {
    0xc800000000000000ull,
};
static UWtype pow5_bits_3[] = {
    0xfa00000000000000ull,
};
static UWtype pow5_bits_4[] = {
    0x9c40000000000000ull,
};
static UWtype pow5_bits_5[] = {
    0xc350000000000000ull,
};
static UWtype pow5_bits_6[] = {
    0xf424000000000000ull,
};
static UWtype pow5_bits_7[] = {
    0x9896800000000000ull,
};
static UWtype pow5_bits_8[] = {
    0xbebc200000000000ull,
};
static UWtype pow5_bits_9[] = {
    0xee6b280000000000ull,
};
static UWtype pow5_bits_10[] = {
    0x9502f90000000000ull,
};
static UWtype pow5_bits_11[] = {
    0xba43b74000000000ull,
};
static UWtype pow5_bits_12[] = {
    0xe8d4a51000000000ull,
};
static UWtype pow5_bits_13[] = {
    0x9184e72a00000000ull,
};
static UWtype pow5_bits_14[] = {
    0xb5e620f480000000ull,
};
static UWtype pow5_bits_15[] = {
    0xe35fa931a0000000ull,
};
static UWtype pow5_bits_16[] = {
    0x8e1bc9bf04000000ull,
};
static UWtype pow5_bits_17[] = {
    0xb1a2bc2ec5000000ull,
};
static UWtype pow5_bits_18[] = {
    0xde0b6b3a76400000ull,
};
static UWtype pow5_bits_19[] = {
    0x8ac7230489e80000ull,
};
static UWtype pow5_bits_20[] = {
    0xad78ebc5ac620000ull,
};
static UWtype pow5_bits_21[] = {
    0xd8d726b7177a8000ull,
};
static UWtype pow5_bits_22[] = {
    0x878678326eac9000ull,
};
static UWtype pow5_bits_23[] = {
    0xa968163f0a57b400ull,
};
static UWtype pow5_bits_24[] = {
    0xd3c21bcecceda100ull,
};
static UWtype pow5_bits_25[] = {
    0x84595161401484a0ull,
};
static UWtype pow5_bits_26[] = {
    0xa56fa5b99019a5c8ull,
};
static UWtype pow5_bits_27[] = {
    0xcecb8f27f4200f3aull,
};
static UWtype pow5_bits_28[] = {
    0x4000000000000000ull,
    0x813f3978f8940984ull,
};
static UWtype pow5_bits_29[] = {
    0x5000000000000000ull,
    0xa18f07d736b90be5ull,
};
static UWtype pow5_bits_30[] = {
    0xa400000000000000ull,
    0xc9f2c9cd04674edeull,
};
static UWtype pow5_bits_31[] = {
    0x4d00000000000000ull,
    0xfc6f7c4045812296ull,
};
static UWtype pow5_bits_32[] = {
    0xf020000000000000ull,
    0x9dc5ada82b70b59dull,
};
static UWtype pow5_bits_33[] = {
    0x6c28000000000000ull,
    0xc5371912364ce305ull,
};
static UWtype pow5_bits_34[] = {
    0xc732000000000000ull,
    0xf684df56c3e01bc6ull,
};
static UWtype pow5_bits_35[] = {
    0x3c7f400000000000ull,
    0x9a130b963a6c115cull,
};
static UWtype pow5_bits_36[] = {
    0x4b9f100000000000ull,
    0xc097ce7bc90715b3ull,
};
static UWtype pow5_bits_37[] = {
    0x1e86d40000000000ull,
    0xf0bdc21abb48db20ull,
};
static UWtype pow5_bits_38[] = {
    0x1314448000000000ull,
    0x96769950b50d88f4ull,
};
static UWtype pow5_bits_39[] = {
    0x17d955a000000000ull,
    0xbc143fa4e250eb31ull,
};
static UWtype pow5_bits_40[] = {
    0x5dcfab0800000000ull,
    0xeb194f8e1ae525fdull,
};
static UWtype pow5_bits_41[] = {
    0x5aa1cae500000000ull,
    0x92efd1b8d0cf37beull,
};
static UWtype pow5_bits_42[] = {
    0xf14a3d9e40000000ull,
    0xb7abc627050305adull,
};
static UWtype pow5_bits_43[] = {
    0x6d9ccd05d0000000ull,
    0xe596b7b0c643c719ull,
};
static UWtype pow5_bits_44[] = {
    0xe4820023a2000000ull,
    0x8f7e32ce7bea5c6full,
};
static UWtype pow5_bits_45[] = {
    0xdda2802c8a800000ull,
    0xb35dbf821ae4f38bull,
};
static UWtype pow5_bits_46[] = {
    0xd50b2037ad200000ull,
    0xe0352f62a19e306eull,
};
static UWtype pow5_bits_47[] = {
    0x4526f422cc340000ull,
    0x8c213d9da502de45ull,
};
static UWtype pow5_bits_48[] = {
    0x9670b12b7f410000ull,
    0xaf298d050e4395d6ull,
};
static UWtype pow5_bits_49[] = {
    0x3c0cdd765f114000ull,
    0xdaf3f04651d47b4cull,
};
static UWtype pow5_bits_50[] = {
    0xa5880a69fb6ac800ull,
    0x88d8762bf324cd0full,
};
static UWtype pow5_bits_51[] = {
    0x8eea0d047a457a00ull,
    0xab0e93b6efee0053ull,
};
static UWtype pow5_bits_52[] = {
    0x72a4904598d6d880ull,
    0xd5d238a4abe98068ull,
};
static UWtype pow5_bits_53[] = {
    0x47a6da2b7f864750ull,
    0x85a36366eb71f041ull,
};
static UWtype pow5_bits_54[] = {
    0x999090b65f67d924ull,
    0xa70c3c40a64e6c51ull,
};
static UWtype pow5_bits_55[] = {
    0xfff4b4e3f741cf6dull,
    0xd0cf4b50cfe20765ull,
};
static UWtype pow5_bits_56[] = {
    0x2000000000000000ull,
    0xbff8f10e7a8921a4ull,
    0x82818f1281ed449full,
};
static UWtype pow5_bits_57[] = {
    0x2800000000000000ull,
    0xaff72d52192b6a0dull,
    0xa321f2d7226895c7ull,
};
static UWtype pow5_bits_58[] = {
    0x7200000000000000ull,
    0x9bf4f8a69f764490ull,
    0xcbea6f8ceb02bb39ull,
};
static UWtype pow5_bits_59[] = {
    0x8e80000000000000ull,
    0x2f236d04753d5b4ull,
    0xfee50b7025c36a08ull,
};
static UWtype pow5_bits_60[] = {
    0xd910000000000000ull,
    0x1d762422c946590ull,
    0x9f4f2726179a2245ull,
};
static UWtype pow5_bits_61[] = {
    0xf54000000000000ull,
    0x424d3ad2b7b97ef5ull,
    0xc722f0ef9d80aad6ull,
};
static UWtype pow5_bits_62[] = {
    0x5329000000000000ull,
    0xd2e0898765a7deb2ull,
    0xf8ebad2b84e0d58bull,
};
static UWtype pow5_bits_63[] = {
    0x73f9a00000000000ull,
    0x63cc55f49f88eb2full,
    0x9b934c3b330c8577ull,
};
static UWtype pow5_bits_64[] = {
    0x50f8080000000000ull,
    0x3cbf6b71c76b25fbull,
    0xc2781f49ffcfa6d5ull,
};
static UWtype pow5_bits_65[] = {
    0x25360a0000000000ull,
    0x8bef464e3945ef7aull,
    0xf316271c7fc3908aull,
};
static UWtype pow5_bits_66[] = {
    0x5741c64000000000ull,
    0x97758bf0e3cbb5acull,
    0x97edd871cfda3a56ull,
};
static UWtype pow5_bits_67[] = {
    0x6d1237d000000000ull,
    0x3d52eeed1cbea317ull,
    0xbde94e8e43d0c8ecull,
};
static UWtype pow5_bits_68[] = {
    0x4856c5c400000000ull,
    0x4ca7aaa863ee4bddull,
    0xed63a231d4c4fb27ull,
};
static UWtype pow5_bits_69[] = {
    0x4d363b9a80000000ull,
    0x8fe8caa93e74ef6aull,
    0x945e455f24fb1cf8ull,
};
static UWtype pow5_bits_70[] = {
    0xe083ca8120000000ull,
    0xb3e2fd538e122b44ull,
    0xb975d6b6ee39e436ull,
};
static UWtype pow5_bits_71[] = {
    0x18a4bd2168000000ull,
    0x60dbbca87196b616ull,
    0xe7d34c64a9c85d44ull,
};
static UWtype pow5_bits_72[] = {
    0xcf66f634e1000000ull,
    0xbc8955e946fe31cdull,
    0x90e40fbeea1d3a4aull,
};
static UWtype pow5_bits_73[] = {
    0x4340b3c219400000ull,
    0x6babab6398bdbe41ull,
    0xb51d13aea4a488ddull,
};
static UWtype pow5_bits_74[] = {
    0x9410e0b29f900000ull,
    0xc696963c7eed2dd1ull,
    0xe264589a4dcdab14ull,
};
static UWtype pow5_bits_75[] = {
    0xfc8a8c6fa3ba0000ull,
    0xfc1e1de5cf543ca2ull,
    0x8d7eb76070a08aecull,
};
static UWtype pow5_bits_76[] = {
    0xbbad2f8b8ca88000ull,
    0x3b25a55f43294bcbull,
    0xb0de65388cc8ada8ull,
};
static UWtype pow5_bits_77[] = {
    0xaa987b6e6fd2a000ull,
    0x49ef0eb713f39ebeull,
    0xdd15fe86affad912ull,
};
static UWtype pow5_bits_78[] = {
    0x2a9f4d2505e3a400ull,
    0x6e3569326c784337ull,
    0x8a2dbf142dfcc7abull,
};
static UWtype pow5_bits_79[] = {
    0xf547206e475c8d00ull,
    0x49c2c37f07965404ull,
    0xacb92ed9397bf996ull,
};
static UWtype pow5_bits_80[] = {
    0x3298e889d933b040ull,
    0xdc33745ec97be906ull,
    0xd7e77a8f87daf7fbull,
};
static UWtype pow5_bits_81[] = {
    0xdf9f915627c04e28ull,
    0x69a028bb3ded71a3ull,
    0x86f0ac99b4e8dafdull,
};
static UWtype pow5_bits_82[] = {
    0xd78775abb1b061b2ull,
    0xc40832ea0d68ce0cull,
    0xa8acd7c0222311bcull,
};
static UWtype pow5_bits_83[] = {
    0x8000000000000000ull,
    0xd6953169e1c7a1eull,
    0xf50a3fa490c30190ull,
    0xd2d80db02aabd62bull,
};
static UWtype pow5_bits_84[] = {
    0x1000000000000000ull,
    0x861d3ee22d1cc53ull,
    0x792667c6da79e0faull,
    0x83c7088e1aab65dbull,
};
static UWtype pow5_bits_85[] = {
    0xd400000000000000ull,
    0x8a7a48e9ab863f67ull,
    0x577001b891185938ull,
    0xa4b8cab1a1563f52ull,
};
static UWtype pow5_bits_86[] = {
    0xc900000000000000ull,
    0xad18db241667cf41ull,
    0xed4c0226b55e6f86ull,
    0xcde6fd5e09abcf26ull,
};
static UWtype pow5_bits_87[] = {
    0x1da0000000000000ull,
    0x2c2f88f68e00e189ull,
    0x544f8158315b05b4ull,
    0x80b05e5ac60b6178ull,
};
static UWtype pow5_bits_88[] = {
    0x6508000000000000ull,
    0x373b6b34318119ebull,
    0x696361ae3db1c721ull,
    0xa0dc75f1778e39d6ull,
};
static UWtype pow5_bits_89[] = {
    0x3e4a000000000000ull,
    0x850a46013de16066ull,
    0x3bc3a19cd1e38e9ull,
    0xc913936dd571c84cull,
};
static UWtype pow5_bits_90[] = {
    0xcddc800000000000ull,
    0xe64cd7818d59b87full,
    0x4ab48a04065c723ull,
    0xfb5878494ace3a5full,
};
static UWtype pow5_bits_91[] = {
    0xe0a9d00000000000ull,
    0x6ff006b0f858134full,
    0x62eb0d64283f9c76ull,
    0x9d174b2dcec0e47bull,
};
static UWtype pow5_bits_92[] = {
    0xd8d4440000000000ull,
    0xbec085d366e1823ull,
    0x3ba5d0bd324f8394ull,
    0xc45d1df942711d9aull,
};
static UWtype pow5_bits_93[] = {
    0xcf09550000000000ull,
    0xee70a7484099e2cull,
    0xca8f44ec7ee36479ull,
    0xf5746577930d6500ull,
};
static UWtype pow5_bits_94[] = {
    0x165d52000000000ull,
    0xa9506688d28602dcull,
    0x7e998b13cf4e1ecbull,
    0x9968bf6abbe85f20ull,
};
static UWtype pow5_bits_95[] = {
    0x1bf4a6800000000ull,
    0x93a4802b07278393ull,
    0x9e3fedd8c321a67eull,
    0xbfc2ef456ae276e8ull,
};
static UWtype pow5_bits_96[] = {
    0xc22f1d0200000000ull,
    0x388da035c8f16477ull,
    0xc5cfe94ef3ea101eull,
    0xefb3ab16c59b14a2ull,
};
static UWtype pow5_bits_97[] = {
    0xd95d722140000000ull,
    0xe35884219d96decaull,
    0xbba1f1d158724a12ull,
    0x95d04aee3b80ece5ull,
};
static UWtype pow5_bits_98[] = {
    0x8fb4cea990000000ull,
    0x9c2ea52a04fc967dull,
    0x2a8a6e45ae8edc97ull,
    0xbb445da9ca61281full,
};
static UWtype pow5_bits_99[] = {
    0xf3a20253f4000000ull,
    0x833a4e74863bbc1cull,
    0xf52d09d71a3293bdull,
    0xea1575143cf97226ull,
};
static UWtype pow5_bits_100[] = {
    0x1845417478800000ull,
    0x72047108d3e55592ull,
    0x593c2626705f9c56ull,
    0x924d692ca61be758ull,
};
static UWtype pow5_bits_101[] = {
    0x9e5691d196a00000ull,
    0xe858d4b08deaaf6ull,
    0x6f8b2fb00c77836cull,
    0xb6e0c377cfa2e12eull,
};
static UWtype pow5_bits_102[] = {
    0x45ec3645fc480000ull,
    0x1226f09dcb1655b4ull,
    0xb6dfb9c0f956447ull,
    0xe498f455c38b997aull,
};
static UWtype pow5_bits_103[] = {
    0xabb3a1ebbdad0000ull,
    0x6b5856629eedf590ull,
    0x4724bd4189bd5eacull,
    0x8edf98b59a373fecull,
};
static UWtype pow5_bits_104[] = {
    0xd6a08a66ad184000ull,
    0x862e6bfb46a972f4ull,
    0x58edec91ec2cb657ull,
    0xb2977ee300c50fe7ull,
};
static UWtype pow5_bits_105[] = {
    0xc48ad00585e5000ull,
    0x67ba06fa1853cfb2ull,
    0x2f2967b66737e3edull,
    0xdf3d5e9bc0f653e1ull,
};
static UWtype pow5_bits_106[] = {
    0x47ad6c20373af200ull,
    0x60d4445c4f3461cfull,
    0xbd79e0d20082ee74ull,
    0x8b865b215899f46cull,
};
static UWtype pow5_bits_107[] = {
    0x1998c7284509ae80ull,
    0x7909557363017a43ull,
    0xecd8590680a3aa11ull,
    0xae67f1e9aec07187ull,
};
static UWtype pow5_bits_108[] = {
    0xdffef8f2564c1a20ull,
    0xd74baad03bc1d8d3ull,
    0xe80e6f4820cc9495ull,
    0xda01ee641a708de9ull,
};
static UWtype pow5_bits_109[] = {
    0x6bff5b9775ef9054ull,
    0xa68f4ac225592784ull,
    0x3109058d147fdcddull,
    0x884134fe908658b2ull,
};
static UWtype pow5_bits_110[] = {
    0x86ff327d536b7469ull,
    0x10331d72aeaf7165ull,
    0xbd4b46f0599fd415ull,
    0xaa51823e34a7eedeull,
};
static UWtype pow5_bits_111[] = {
    0x4000000000000000ull,
    0xe8beff1ca8465183ull,
    0x543fe4cf5a5b4dbeull,
    0x6c9e18ac7007c91aull,
    0xd4e5e2cdc1d1ea96ull,
};
static UWtype pow5_bits_112[] = {
    0x800000000000000ull,
    0x51775f71e92bf2f2ull,
    0x74a7ef0198791097ull,
    0x3e2cf6bc604ddb0ull,
    0x850fadc09923329eull,
};
static UWtype pow5_bits_113[] = {
    0x8a00000000000000ull,
    0x25d5374e6376efaeull,
    0x91d1eac1fe9754bdull,
    0x84db8346b786151cull,
    0xa6539930bf6bff45ull,
};
static UWtype pow5_bits_114[] = {
    0x2c80000000000000ull,
    0x6f4a8521fc54ab9aull,
    0xb64665727e3d29ecull,
    0xe612641865679a63ull,
    0xcfe87f7cef46ff16ull,
};
static UWtype pow5_bits_115[] = {
    0x5bd0000000000000ull,
    0xc58e93353db4eb40ull,
    0x51ebff678ee63a33ull,
    0x4fcb7e8f3f60c07eull,
    0x81f14fae158c5f6eull,
};
static UWtype pow5_bits_116[] = {
    0x72c4000000000000ull,
    0xb6f238028d222610ull,
    0xe666ff41729fc8c0ull,
    0xe3be5e330f38f09dull,
    0xa26da3999aef7749ull,
};
static UWtype pow5_bits_117[] = {
    0x8f75000000000000ull,
    0xe4aec603306aaf94ull,
    0x6000bf11cf47baf0ull,
    0x5cadf5bfd3072cc5ull,
    0xcb090c8001ab551cull,
};
static UWtype pow5_bits_118[] = {
    0xb352400000000000ull,
    0x1dda7783fc855b79ull,
    0xb800eed64319a9adull,
    0x73d9732fc7c8f7f6ull,
    0xfdcb4fa002162a63ull,
};
static UWtype pow5_bits_119[] = {
    0x1013680000000000ull,
    0x32a88ab27dd3592cull,
    0x33009545e9f00a0cull,
    0x2867e7fddcdd9afaull,
    0x9e9f11c4014dda7eull,
};
static UWtype pow5_bits_120[] = {
    0x1418420000000000ull,
    0x3f52ad5f1d482f77ull,
    0xbfc0ba97646c0c8full,
    0xb281e1fd541501b8ull,
    0xc646d63501a1511dull,
};
static UWtype pow5_bits_121[] = {
    0xd91e528000000000ull,
    0xf2758b6e49a3b54ull,
    0xefb0e93d3d870fb3ull,
    0x1f225a7ca91a4226ull,
    0xf7d88bc24209a565ull,
};
static UWtype pow5_bits_122[] = {
    0x7b2f39000000000ull,
    0xe97897724ee06515ull,
    0x55ce91c6467469cfull,
    0x3375788de9b06958ull,
    0x9ae757596946075full,
};
static UWtype pow5_bits_123[] = {
    0x499fb07400000000ull,
    0xe3d6bd4ee2987e5aull,
    0x6b423637d8118443ull,
    0x52d6b1641c83aeull,
    0xc1a12d2fc3978937ull,
};
static UWtype pow5_bits_124[] = {
    0xdc079c9100000000ull,
    0xdccc6ca29b3e9df0ull,
    0x612c3c5ce15e554ull,
    0xc0678c5dbd23a49aull,
    0xf209787bb47d6b84ull,
};
static UWtype pow5_bits_125[] = {
    0x8984c1daa0000000ull,
    0x9ffc3e5a10722b6ull,
    0x43cbba5ba0cdaf55ull,
    0xf840b7ba963646e0ull,
    0x9745eb4d50ce6332ull,
};
static UWtype pow5_bits_126[] = {
    0x2be5f25148000000ull,
    0x4c7fb4df0948eb64ull,
    0x54bea8f289011b2aull,
    0xb650e5a93bc3d898ull,
    0xbd176620a501fbffull,
};
static UWtype pow5_bits_127[] = {
    0x36df6ee59a000000ull,
    0xdf9fa216cb9b263dull,
    0x69ee532f2b4161f4ull,
    0xa3e51f138ab4cebeull,
    0xec5d3fa8ce427affull,
};
static UWtype pow5_bits_128[] = {
    0x424ba54f80400000ull,
    0xbc3c54e3f40f7e6ull,
    0x234f3fd7b08dd39ull,
    0xc66f336c36b10137ull,
    0x93ba47c980e98cdfull,
};
static UWtype pow5_bits_129[] = {
    0xd2de8ea360500000ull,
    0x4eb4b6a1cf1135dfull,
    0xc2c230fcd9cb1487ull,
    0xb80b0047445d4184ull,
    0xb8a8d9bbe123f017ull,
};
static UWtype pow5_bits_130[] = {
    0xc796324c38640000ull,
    0x2261e44a42d58357ull,
    0xf372bd3c103dd9a9ull,
    0xa60dc059157491e5ull,
    0xe6d3102ad96cec1dull,
};
static UWtype pow5_bits_131[] = {
    0xdcbddf6fa33e8000ull,
    0xb57d2eae69c57216ull,
    0xb827b6458a26a809ull,
    0x87c89837ad68db2full,
    0x9043ea1ac7e41392ull,
};
static UWtype pow5_bits_132[] = {
    0x93ed574b8c0e2000ull,
    0x22dc7a5a0436ce9cull,
    0xa631a3d6ecb0520cull,
    0x29babe4598c311fbull,
    0xb454e4a179dd1877ull,
};
static UWtype pow5_bits_133[] = {
    0xb8e8ad1e6f11a800ull,
    0x2b9398f085448243ull,
    0x8fbe0ccca7dc668full,
    0xf4296dd6fef3d67aull,
    0xe16a1dc9d8545e94ull,
};
static UWtype pow5_bits_134[] = {
    0x53916c33056b0900ull,
    0x7b3c3f96534ad16aull,
    0x99d6c7ffe8e9c019ull,
    0x1899e4a65f58660cull,
    0x8ce2529e2734bb1dull,
};
static UWtype pow5_bits_135[] = {
    0xe875c73fc6c5cb40ull,
    0xda0b4f7be81d85c4ull,
    0xc04c79ffe324301full,
    0x5ec05dcff72e7f8full,
    0xb01ae745b101e9e4ull,
};
static UWtype pow5_bits_136[] = {
    0x2293390fb8773e10ull,
    0xd08e235ae224e736ull,
    0xb05f987fdbed3c27ull,
    0x76707543f4fa1f73ull,
    0xdc21a1171d42645dull,
};
static UWtype pow5_bits_137[] = {
    0xd59c03a9d34a86caull,
    0xe258d618cd571081ull,
    0x4e3bbf4fe9744598ull,
    0x6a06494a791c53a8ull,
    0x899504ae72497ebaull,
};
static UWtype pow5_bits_138[] = {
    0x8000000000000000ull,
    0x4b030494481d287cull,
    0x1aef0b9f00acd4a2ull,
    0x61caaf23e3d156ffull,
    0x487db9d17636892ull,
    0xabfa45da0edbde69ull,
};
static UWtype pow5_bits_139[] = {
    0xa000000000000000ull,
    0xddc3c5b95a24729bull,
    0xe1aace86c0d809caull,
    0xfa3d5aecdcc5acbeull,
    0x45a9d2845d3c42b6ull,
    0xd6f8d7509292d603ull,
};
static UWtype pow5_bits_140[] = {
    0x4400000000000000ull,
    0xca9a5b93d856c7a1ull,
    0x4d0ac1143887061eull,
    0x5c6658d409fb8bf7ull,
    0xb8a2392ba45a9b2ull,
    0x865b86925b9bc5c2ull,
};
static UWtype pow5_bits_141[] = {
    0x9500000000000000ull,
    0x7d40f278ce6c7989ull,
    0x204d715946a8c7a6ull,
    0xf37fef090c7a6ef5ull,
    0x8e6cac7768d7141eull,
    0xa7f26836f282b732ull,
};
static UWtype pow5_bits_142[] = {
    0xfa40000000000000ull,
    0x1c912f17020797ebull,
    0x6860cdaf9852f990ull,
    0xb05feacb4f990ab2ull,
    0x3207d795430cd926ull,
    0xd1ef0244af2364ffull,
};
static UWtype pow5_bits_143[] = {
    0x7c68000000000000ull,
    0x11dabd6e6144bef3ull,
    0x813c808dbf33dbfaull,
    0x2e3bf2bf11bfa6afull,
    0x7f44e6bd49e807b8ull,
    0x8335616aed761f1full,
};
static UWtype pow5_bits_144[] = {
    0x5b82000000000000ull,
    0x96516cc9f995eeb0ull,
    0x618ba0b12f00d2f8ull,
    0x39caef6ed62f905bull,
    0x5f16206c9c6209a6ull,
    0xa402b9c5a8d3a6e7ull,
};
static UWtype pow5_bits_145[] = {
    0x7262800000000000ull,
    0xbbe5c7fc77fb6a5cull,
    0x39ee88dd7ac107b6ull,
    0xc83dab4a8bbb7472ull,
    0x36dba887c37a8c0full,
    0xcd036837130890a1ull,
};
static UWtype pow5_bits_146[] = {
    0xc77d900000000000ull,
    0x356f9cfdcafd2279ull,
    0x6435158a6cb8a4d2ull,
    0xdd268b0e975528c7ull,
    0xc2494954da2c9789ull,
    0x802221226be55a64ull,
};
static UWtype pow5_bits_147[] = {
    0x395cf40000000000ull,
    0xc2cb843d3dbc6b18ull,
    0x3d425aed07e6ce06ull,
    0x54702dd23d2a72f9ull,
    0xf2db9baa10b7bd6cull,
    0xa02aa96b06deb0fdull,
};
static UWtype pow5_bits_148[] = {
    0x47b4310000000000ull,
    0x737e654c8d2b85deull,
    0x8c92f1a849e08188ull,
    0x698c3946cc750fb7ull,
    0x6f92829494e5acc7ull,
    0xc83553c5c8965d3dull,
};
static UWtype pow5_bits_149[] = {
    0xd9a13d4000000000ull,
    0x905dfe9fb0766755ull,
    0x6fb7ae125c58a1eaull,
    0x43ef47987f9253a5ull,
    0xcb772339ba1f17f9ull,
    0xfa42a8b73abbf48cull,
};
static UWtype pow5_bits_150[] = {
    0xa804c64800000000ull,
    0x9a3abf23ce4a0095ull,
    0x65d2cccb79b76532ull,
    0xca758cbf4fbb7447ull,
    0xff2a760414536efbull,
    0x9c69a97284b578d7ull,
};
static UWtype pow5_bits_151[] = {
    0x1205f7da00000000ull,
    0x40c96eecc1dc80bbull,
    0x3f477ffe58253e7full,
    0xbd12efef23aa5159ull,
    0xfef5138519684abaull,
    0xc38413cf25e2d70dull,
};
static UWtype pow5_bits_152[] = {
    0xd68775d080000000ull,
    0x10fbcaa7f253a0e9ull,
    0x8f195ffdee2e8e1full,
    0x6c57abeaec94e5afull,
    0x7eb258665fc25d69ull,
    0xf46518c2ef5b8cd1ull,
};
static UWtype pow5_bits_153[] = {
    0x2614a9a250000000ull,
    0x6a9d5ea8f7744492ull,
    0xb96fdbfeb4dd18d3ull,
    0xe3b6cb72d3dd0f8dull,
    0xef2f773ffbd97a61ull,
    0x98bf2f79d5993802ull,
};
static UWtype pow5_bits_154[] = {
    0xaf99d40ae4000000ull,
    0x4544b653355155b6ull,
    0x27cbd2fe62145f08ull,
    0x5ca47e4f88d45371ull,
    0xaafb550ffacfd8faull,
    0xbeeefb584aff8603ull,
};
static UWtype pow5_bits_155[] = {
    0x5b80490d9d000000ull,
    0x5695e3e802a5ab24ull,
    0x71bec7bdfa9976caull,
    0xf3cd9de36b09684dull,
    0x95ba2a53f983cf38ull,
    0xeeaaba2e5dbf6784ull,
};
static UWtype pow5_bits_156[] = {
    0xb9302da882200000ull,
    0x761dae7101a78af6ull,
    0x67173cd6bc9fea3eull,
    0x986082ae22e5e130ull,
    0xdd945a747bf26183ull,
    0x952ab45cfa97a0b2ull,
};
static UWtype pow5_bits_157[] = {
    0x677c3912a2a80000ull,
    0x13a51a0d42116db4ull,
    0x80dd0c0c6bc7e4ceull,
    0x7e78a359ab9f597cull,
    0x94f971119aeef9e4ull,
    0xba756174393d88dfull,
};
static UWtype pow5_bits_158[] = {
    0x815b47574b520000ull,
    0x988e60909295c921ull,
    0xa1144f0f86b9de01ull,
    0x9e16cc3016872fdbull,
    0x7a37cd5601aab85dull,
    0xe912b9d1478ceb17ull,
};
static UWtype pow5_bits_159[] = {
    0xf0d90c968f134000ull,
    0xff58fc5a5b9d9db4ull,
    0x44acb169b4342ac0ull,
    0x82ce3f9e0e147de9ull,
    0xac62e055c10ab33aull,
    0x91abb422ccb812eeull,
};
static UWtype pow5_bits_160[] = {
    0x2d0f4fbc32d81000ull,
    0x3f2f3b70f2850522ull,
    0x95d7ddc421413571ull,
    0x2381cf8591999d63ull,
    0x577b986b314d6009ull,
    0xb616a12b7fe617aaull,
};
static UWtype pow5_bits_161[] = {
    0xb85323ab3f8e1400ull,
    0x8efb0a4d2f26466aull,
    0x7b4dd535299182cdull,
    0x6c624366f60004bcull,
    0xed5a7e85fda0b80bull,
    0xe39c49765fdf9d94ull,
};
static UWtype pow5_bits_162[] = {
    0xb333f64b07b8cc80ull,
    0x795ce6703d77ec02ull,
    0xcd10a54139faf1c0ull,
    0x23bd6a2059c002f5ull,
    0x14588f13be847307ull,
    0x8e41ade9fbebc27dull,
};
static UWtype pow5_bits_163[] = {
    0x6000f3ddc9a6ffa0ull,
    0x97b4200c4cd5e703ull,
    0x4054ce918879ae30ull,
    0xecacc4a8703003b3ull,
    0x596eb2d8ae258fc8ull,
    0xb1d219647ae6b31cull,
};
static UWtype pow5_bits_164[] = {
    0x380130d53c10bf88ull,
    0xbda1280f600b60c4ull,
    0x106a0235ea9819bcull,
    0x27d7f5d28c3c04a0ull,
    0x6fca5f8ed9aef3bbull,
    0xde469fbd99a05fe3ull,
};
static UWtype pow5_bits_165[] = {
    0xa300be85458a77b5ull,
    0xf684b9099c071c7aull,
    0xa424161b29f1015ull,
    0xf8e6f9a397a582e4ull,
    0x25de7bb9480d5854ull,
    0x8aec23d680043beeull,
};
static UWtype pow5_bits_166[] = {
    0x4000000000000000ull,
    0x4bc0ee2696ed15a2ull,
    0x7425e74c0308e399ull,
    0xcd2d1ba1f46d41bull,
    0x3720b80c7d8ee39dull,
    0xaf561aa79a10ae6aull,
    0xada72ccc20054ae9ull,
};
static UWtype pow5_bits_167[] = {
    0xd000000000000000ull,
    0x9eb129b03ca85b0aull,
    0x512f611f03cb1c7full,
    0x50078628a7188922ull,
    0xc4e8e60f9cf29c84ull,
    0x1b2ba1518094da04ull,
    0xd910f7ff28069da4ull,
};
static UWtype pow5_bits_168[] = {
    0xc200000000000000ull,
    0xc32eba0e25e938e6ull,
    0x72bd9cb3625ef1cfull,
    0xb204b3d9686f55b5ull,
    0xfb118fc9c217a1d2ull,
    0x90fb44d2f05d0842ull,
    0x87aa9aff79042286ull,
};
static UWtype pow5_bits_169[] = {
    0x7280000000000000ull,
    0xb3fa6891af638720ull,
    0xcf6d03e03af6ae43ull,
    0x5e85e0cfc28b2b22ull,
    0xb9d5f3bc329d8a47ull,
    0x353a1607ac744a53ull,
    0xa99541bf57452b28ull,
};
static UWtype pow5_bits_170[] = {
    0x8f20000000000000ull,
    0xa0f902b61b3c68e8ull,
    0x834844d849b459d4ull,
    0x36275903b32df5ebull,
    0xa84b70ab3f44ecd9ull,
    0x42889b8997915ce8ull,
    0xd3fa922f2d1675f2ull,
};
static UWtype pow5_bits_171[] = {
    0x5974000000000000ull,
    0xe49ba1b1d105c191ull,
    0x320d2b072e10b824ull,
    0xc1d897a24ffcb9b3ull,
    0x692f266b078b1407ull,
    0x69956135febada11ull,
    0x847c9b5d7c2e09b7ull,
};
static UWtype pow5_bits_172[] = {
    0xafd1000000000000ull,
    0x1dc28a1e454731f5ull,
    0xfe9075c8f994e62eull,
    0xb24ebd8ae3fbe81full,
    0xc37af005c96dd909ull,
    0x43fab9837e699095ull,
    0xa59bc234db398c25ull,
};
static UWtype pow5_bits_173[] = {
    0x1bc5400000000000ull,
    0xa5332ca5d698fe73ull,
    0xfe34933b37fa1fb9ull,
    0x1ee26ced9cfae227ull,
    0x3459ac073bc94f4cull,
    0x94f967e45e03f4bbull,
    0xcf02b2c21207ef2eull,
};
static UWtype pow5_bits_174[] = {
    0xf15b480000000000ull,
    0x73ffbe7a61f9f07ull,
    0xfee0dc0502fc53d4ull,
    0x934d8414821ccd58ull,
    0xb80b84855dd18full,
    0x1d1be0eebac278f5ull,
    0x8161afb94b44f57dull,
};
static UWtype pow5_bits_175[] = {
    0xedb21a0000000000ull,
    0x90ffae18fa786c9ull,
    0x3e99130643bb68c9ull,
    0x7820e519a2a400afull,
    0x40e60e65a6b545f3ull,
    0x6462d92a69731732ull,
    0xa1ba1ba79e1632dcull,
};
static UWtype pow5_bits_176[] = {
    0x691ea08000000000ull,
    0x4b53f999f391687cull,
    0xe3f57c7d4aa42fbull,
    0x56291e600b4d00dbull,
    0xd11f91ff10629770ull,
    0x7d7b8f7503cfdcfeull,
    0xca28a291859bbf93ull,
};
static UWtype pow5_bits_177[] = {
    0x836648a000000000ull,
    0x1e28f8007075c29bull,
    0xd1cf2db9c9d4d3baull,
    0x6bb365f80e204111ull,
    0x8567767ed47b3d4cull,
    0x5cda735244c3d43eull,
    0xfcb2cb35e702af78ull,
};
static UWtype pow5_bits_178[] = {
    0x321fed6400000000ull,
    0x52d99b00464999a1ull,
    0x23217c941e250454ull,
    0xc3501fbb08d428abull,
    0x1360aa0f44cd064full,
    0x3a0888136afa64a7ull,
    0x9defbf01b061adabull,
};
static UWtype pow5_bits_179[] = {
    0x7ea7e8bd00000000ull,
    0x679001c057dc0009ull,
    0xebe9dbb925ae4569ull,
    0xb42427a9cb0932d5ull,
    0xd838d493160047e3ull,
    0x88aaa1845b8fdd0ull,
    0xc56baec21c7a1916ull,
};
static UWtype pow5_bits_180[] = {
    0xde51e2ec40000000ull,
    0xc17402306dd3000bull,
    0x66e452a76f19d6c3ull,
    0xa12d31943dcb7f8bull,
    0xe4709b7db8059dcull,
    0x8aad549e57273d45ull,
    0xf6c69a72a3989f5bull,
};
static UWtype pow5_bits_181[] = {
    0x6af32dd3a8000000ull,
    0x58e8815e44a3e007ull,
    0x204eb3a8a570263aull,
    0xe4bc3efca69f2fb7ull,
    0x28ec6612e9303829ull,
    0x36ac54e2f678864bull,
    0x9a3c2087a63f6399ull,
};
static UWtype pow5_bits_182[] = {
    0x45aff94892000000ull,
    0xef22a1b5d5ccd809ull,
    0xe8626092cecc2fc8ull,
    0x5deb4ebbd046fba4ull,
    0xf3277f97a37c4634ull,
    0x84576a1bb416a7ddull,
    0xc0cb28a98fcf3c7full,
};
static UWtype pow5_bits_183[] = {
    0x971bf79ab6800000ull,
    0x2aeb4a234b400e0bull,
    0x227af8b7827f3bbbull,
    0x7566226ac458ba8eull,
    0x6ff15f7d8c5b57c1ull,
    0x656d44a2a11c51d5ull,
    0xf0fdf2d3f3c30b9full,
};
static UWtype pow5_bits_184[] = {
    0x3e717ac0b2100000ull,
    0xfad30e560f0808c7ull,
    0xd58cdb72b18f8554ull,
    0xe95fd582bab77498ull,
    0x65f6dbae77b916d8ull,
    0x9f644ae5a4b1b325ull,
    0x969eb7c47859e743ull,
};
static UWtype pow5_bits_185[] = {
    0xe0dd970de940000ull,
    0x3987d1eb92ca0af9ull,
    0xaf0124f5df366aaull,
    0x23b7cae3696551bfull,
    0xbf74929a15a75c8full,
    0x873d5d9f0dde1feeull,
    0xbc4665b596706114ull,
};
static UWtype pow5_bits_186[] = {
    0x51914fcd16390000ull,
    0xc7e9c666777c8db7ull,
    0xcdac16e335704054ull,
    0xeca5bd9c43bea62eull,
    0x6f51b7409b1133b2ull,
    0xa90cb506d155a7eaull,
    0xeb57ff22fc0c7959ull,
};
static UWtype pow5_bits_187[] = {
    0x92fad1e02de3a000ull,
    0xfcf21c000aadd892ull,
    0x408b8e4e01662834ull,
    0xd3e79681aa5727ddull,
    0x8593128860eac04full,
    0x9a7f12442d588f2ull,
    0x9316ff75dd87cbd8ull,
};
static UWtype pow5_bits_188[] = {
    0x37b98658395c8800ull,
    0x3c2ea3000d594eb7ull,
    0x90ae71e181bfb242ull,
    0xc8e17c2214ecf1d4ull,
    0x26f7d72a79257063ull,
    0xc11ed6d538aeb2full,
    0xb7dcbf5354e9beceull,
};
static UWtype pow5_bits_189[] = {
    0x5a7e7ee47b3aa00ull,
    0xcb3a4bc010afa265ull,
    0xb4da0e59e22f9ed2ull,
    0xbb19db2a9a282e49ull,
    0xf0b5ccf5176ecc7cull,
    0x8f1668c8a86da5faull,
    0xe5d3ef282a242e81ull,
};
static UWtype pow5_bits_190[] = {
    0x2388f0f4ecd04a40ull,
    0xbf046f580a6dc57full,
    0x110848f82d5dc343ull,
    0xf4f028faa0591ceeull,
    0xd671a0192ea53fcdull,
    0xf96e017d694487bcull,
    0x8fa475791a569d10ull,
};
static UWtype pow5_bits_191[] = {
    0xec6b2d3228045cd0ull,
    0xaec58b2e0d0936deull,
    0x954a5b3638b53414ull,
    0x722c3339486f6429ull,
    0xc0e081f7a4e8fc1ull,
    0x37c981dcc395a9acull,
    0xb38d92d760ec4455ull,
};
static UWtype pow5_bits_192[] = {
    0xa785f87eb2057404ull,
    0xda76edf9904b8496ull,
    0xfa9cf203c6e28119ull,
    0xceb740079a8b3d33ull,
    0xf118a2758e233b1ull,
    0x85bbe253f47b1417ull,
    0xe070f78d3927556aull,
};
static UWtype pow5_bits_193[] = {
    0x8000000000000000ull,
    0x28b3bb4f2f436882ull,
    0x288a54bbfa2f32deull,
    0x7ca217425c4d90b0ull,
    0x21328804c0970640ull,
    0x696af658978d604full,
    0x93956d7478ccec8eull,
    0x8c469ab843b89562ull,
};
static UWtype pow5_bits_194[] = {
    0x2000000000000000ull,
    0xb2e0aa22fb1442a3ull,
    0x32ace9eaf8baff95ull,
    0x9bca9d12f360f4dcull,
    0xe97f2a05f0bcc7d0ull,
    0x3c5b3eebd70b862ull,
    0x387ac8d1970027b2ull,
    0xaf58416654a6babbull,
};
static UWtype pow5_bits_195[] = {
    0xe800000000000000ull,
    0x1f98d4abb9d9534bull,
    0x3f582465b6e9bf7bull,
    0xc2bd4457b0393213ull,
    0xa3def4876cebf9c4ull,
    0x84b720ea6ccce67bull,
    0x6997b05fcc0319eull,
    0xdb2e51bfe9d0696aull,
};
static UWtype pow5_bits_196[] = {
    0x7100000000000000ull,
    0xf3bf84eb5427d40full,
    0x79716bf925217acull,
    0xf9b64ab6ce23bf4cull,
    0x466b58d4a4137c1aull,
    0x12f274928400100dull,
    0x441fece3bdf81f03ull,
    0x88fcf317f22241e2ull,
};
static UWtype pow5_bits_197[] = {
    0x4d40000000000000ull,
    0x30af66262931c913ull,
    0x97cdc6f76e69d98ull,
    0xb823dd6481acaf1full,
    0x98062f09cd185b21ull,
    0xd7af11b725001410ull,
    0xd527e81cad7626c3ull,
    0xab3c2fddeeaad25aull,
};
static UWtype pow5_bits_198[] = {
    0x2090000000000000ull,
    0x3cdb3fafb37e3b58ull,
    0xcbdc138b54a044feull,
    0x262cd4bda217dae6ull,
    0xbe07bacc405e71eaull,
    0xcd9ad624ee401914ull,
    0x8a71e223d8d3b074ull,
    0xd60b3bd56a5586f1ull,
};
static UWtype pow5_bits_199[] = {
    0x145a000000000000ull,
    0xe60907cdd02ee517ull,
    0x3f698c3714e42b1eull,
    0x57dc04f6854ee8d0ull,
    0xf6c4d4bfa83b0732ull,
    0x80c5d714e80facull,
    0xf6872d5667844e49ull,
    0x85c7056562757456ull,
};
static UWtype pow5_bits_200[] = {
    0xd970800000000000ull,
    0x9f8b49c1443a9e5cull,
    0x4f43ef44da1d35e6ull,
    0xedd3063426a2a304ull,
    0x347609ef9249c8feull,
    0x40a0f74cda221398ull,
    0xb428f8ac016561dbull,
    0xa738c6bebb12d16cull,
};
static UWtype pow5_bits_201[] = {
    0xfcca00000000000ull,
    0x476e1c31954945f4ull,
    0x6314eb1610a48360ull,
    0xa947c7c1304b4bc5ull,
    0x41938c6b76dc3b3eull,
    0x10c9352010aa987eull,
    0xe13336d701beba52ull,
    0xd106f86e69d785c7ull,
};
static UWtype pow5_bits_202[] = {
    0x89dfe40000000000ull,
    0x2ca4d19efd4dcbb8ull,
    0x5ded12edca66d21cull,
    0x29ccdcd8be2f0f5bull,
    0xe8fc37c32a49a507ull,
    0x4a7dc1340a6a9f4eull,
    0xecc0024661173473ull,
    0x82a45b450226b39cull,
};
static UWtype pow5_bits_203[] = {
    0xac57dd0000000000ull,
    0x37ce0606bca13ea6ull,
    0x356857a93d0086a3ull,
    0xf440140eedbad332ull,
    0xa33b45b3f4dc0e48ull,
    0x1d1d31810d054722ull,
    0x27f002d7f95d0190ull,
    0xa34d721642b06084ull,
};
static UWtype pow5_bits_204[] = {
    0x576dd44000000000ull,
    0x5c187886bc98e50ull,
    0xc2c26d938c40a84cull,
    0x31501912a92987feull,
    0x4c0a1720f21311dbull,
    0x24647de1504698ebull,
    0x31ec038df7b441f4ull,
    0xcc20ce9bd35c78a5ull,
};
static UWtype pow5_bits_205[] = {
    0x6d49495000000000ull,
    0x731e96a86bbf1e4ull,
    0x737308f86f50d25full,
    0xfda41f575373e9feull,
    0x1f0c9ce92e97d651ull,
    0x2d7d9d59a4583f26ull,
    0x7e67047175a15271ull,
    0xff290242c83396ceull,
};
static UWtype pow5_bits_206[] = {
    0xc44dcdd200000000ull,
    0x647f31e29435772eull,
    0x827e59b4592837bull,
    0x3e8693969428723full,
    0xd367e211bd1ee5f3ull,
    0xbc6e825806b72777ull,
    0xf0062c6e984d386ull,
    0x9f79a169bd203e41ull,
};
static UWtype pow5_bits_207[] = {
    0x7561414680000000ull,
    0x3d9efe5b3942d4faull,
    0xca31df0216f7245aull,
    0xe28387c39328eceull,
    0xc841da962c669f70ull,
    0x6b8a22ee0864f155ull,
    0x52c07b78a3e60868ull,
    0xc75809c42c684dd1ull,
};
static UWtype pow5_bits_208[] = {
    0x12b9919820000000ull,
    0xcd06bdf207938a39ull,
    0x7cbe56c29cb4ed70ull,
    0x11b2469b477f3282ull,
    0x3a52513bb780474cull,
    0x866caba98a7e2dabull,
    0xa7709a56ccdf8a82ull,
    0xf92e0c3537826145ull,
};
static UWtype pow5_bits_209[] = {
    0xabb3faff14000000ull,
    0x802436b744bc3663ull,
    0x8df6f639a1f11466ull,
    0x8b0f6c210caf7f91ull,
    0x47372c552b02c8full,
    0x9403eb49f68edc8bull,
    0x88a66076400bb691ull,
    0x9bbcc7a142b17ccbull,
};
static UWtype pow5_bits_210[] = {
    0x96a0f9bed9000000ull,
    0x202d446515eb43fcull,
    0xf174b3c80a6d5980ull,
    0x6dd347294fdb5f75ull,
    0xc5904f76a75c37b3ull,
    0xf904e61c743293adull,
    0x6acff893d00ea435ull,
    0xc2abf989935ddbfeull,
};
static UWtype pow5_bits_211[] = {
    0xbc49382e8f400000ull,
    0x2838957e5b6614fbull,
    0x6dd1e0ba0d08afe0ull,
    0x494818f3a3d23753ull,
    0x36f46354513345a0ull,
    0x77461fa3913f3899ull,
    0x583f6b8c4124d43ull,
    0xf356f7ebf83552feull,
};
static UWtype pow5_bits_212[] = {
    0x55adc31d19880000ull,
    0x19235d6ef91fcd1dull,
    0x24a32c7448256decull,
    0x2dcd0f9846636294ull,
    0xc258be14b2c00b84ull,
    0x2a8bd3c63ac7835full,
    0xc3727a337a8b704aull,
    0x98165af37b2153deull,
};
static UWtype pow5_bits_213[] = {
    0xab1933e45fea0000ull,
    0x1f6c34cab767c064ull,
    0x2dcbf7915a2ec967ull,
    0x3940537e57fc3b39ull,
    0xb2eeed99df700e65ull,
    0xb52ec8b7c9796437ull,
    0x744f18c0592e4c5cull,
    0xbe1bf1b059e9a8d6ull,
};
static UWtype pow5_bits_214[] = {
    0xd5df80dd77e48000ull,
    0xe74741fd6541b07dull,
    0x793ef575b0ba7bc0ull,
    0x8790685dedfb4a07ull,
    0x9faaa900574c11feull,
    0xe27a7ae5bbd7bd45ull,
    0x1162def06f79df73ull,
    0xeda2ee1c7064130cull,
};
static UWtype pow5_bits_215[] = {
    0xa5abb08a6aeed000ull,
    0x908c893e5f490e4eull,
    0xabc759698e748d58ull,
    0x14ba413ab4bd0e44ull,
    0x83caa9a0368f8b3full,
    0x6d8c8ccf9566d64bull,
    0x8addcb5645ac2ba8ull,
    0x9485d4d1c63e8be7ull,
};
static UWtype pow5_bits_216[] = {
    0x4f169cad05aa8400ull,
    0xb4afab8df71b51e2ull,
    0xd6b92fc3f211b0aeull,
    0xd9e8d18961ec51d5ull,
    0x64bd540844336e0eull,
    0x88efb0037ac08bdeull,
    0x6d953e2bd7173692ull,
    0xb9a74a0637ce2ee1ull,
};
static UWtype pow5_bits_217[] = {
    0xe2dc43d847152500ull,
    0x61db967174e2265aull,
    0x4c677bb4ee961cdaull,
    0x906305ebba67664bull,
    0xfdeca90a55404992ull,
    0x2b2b9c045970aed5ull,
    0xc8fa8db6ccdd0437ull,
    0xe8111c87c5c1ba99ull,
};
static UWtype pow5_bits_218[] = {
    0xcdc9aa672c6d3720ull,
    0x7d293e06e90d57f8ull,
    0xfc0ad51151dd208ull,
    0x9a3de3b354809fefull,
    0xbeb3e9a675482dfbull,
    0x7afb4182b7e66d45ull,
    0x1d9c9892400a22a2ull,
    0x910ab1d4db9914a0ull,
};
static UWtype pow5_bits_219[] = {
    0x13c1500f78884e8ull,
    0x9c738d88a350adf7ull,
    0xd3b0d8a55a65468aull,
    0x80cd5ca029a0c7eaull,
    0x2e60e410129a397aull,
    0x19ba11e365e00897ull,
    0x2503beb6d00cab4bull,
    0xb54d5e4a127f59c8ull,
};
static UWtype pow5_bits_220[] = {
    0xc18b1a41356aa622ull,
    0x439070eacc24d974ull,
    0x889d0eceb0fe982dull,
    0x2100b3c83408f9e5ull,
    0xf9f91d141740c7d9ull,
    0xe028965c3f580abcull,
    0x2e44ae64840fd61dull,
    0xe2a0b5dc971f303aull,
};
static UWtype pow5_bits_221[] = {
    0x4000000000000000ull,
    0xf8f6f068c162a7d5ull,
    0x4a3a4692bf9707e8ull,
    0x756229412e9f1f1cull,
    0xb4a0705d20859c2full,
    0x1c3bb22c8e887ce7ull,
    0xac195df9a79706b6ull,
    0x5ceaecfed289e5d2ull,
    0x8da471a9de737e24ull,
};
static UWtype pow5_bits_222[] = {
    0x9000000000000000ull,
    0x3734ac82f1bb51caull,
    0x5cc8d8376f7cc9e3ull,
    0x52bab3917a46e6e3ull,
    0xa1c88c7468a7033bull,
    0xa34a9eb7b22a9c21ull,
    0x571fb578117cc863ull,
    0x7425a83e872c5f47ull,
    0xb10d8e1456105dadull,
};
static UWtype pow5_bits_223[] = {
    0x3400000000000000ull,
    0x501d7a3ae2a263dull,
    0x33fb0e454b5bfc5cull,
    0x27696075d8d8a09cull,
    0xa3aaf9182d0c40aull,
    0x8c1d46659eb5432aull,
    0x2ce7a2d615dbfa7cull,
    0xd12f124e28f77719ull,
    0xdd50f1996b947518ull,
};
static UWtype pow5_bits_224[] = {
    0x4080000000000000ull,
    0x832126c64cda57e6ull,
    0xa07ce8eb4f197db9ull,
    0x58a1dc49a7876461ull,
    0x4664adbaf1c27a86ull,
    0xd7924bff833149faull,
    0xbc10c5c5cda97c8dull,
    0x82bd6b70d99aaa6full,
    0x8a5296ffe33cc92full,
};
static UWtype pow5_bits_225[] = {
    0xd0a0000000000000ull,
    0xe3e97077e010eddfull,
    0x89c232622dfdd27ull,
    0xeeca535c11693d7aull,
    0xd7fdd929ae331927ull,
    0x4d76deff63fd9c78ull,
    0xab14f7374113dbb1ull,
    0x636cc64d1001550bull,
    0xace73cbfdc0bfb7bull,
};
static UWtype pow5_bits_226[] = {
    0xc4c8000000000000ull,
    0xdce3cc95d8152957ull,
    0x8ac32befab97d471ull,
    0xea7ce83315c38cd8ull,
    0xdfd4f7419bfdf71ull,
    0xa0d496bf3cfd0397ull,
    0x95da35051158d29dull,
    0x3c47f7e05401aa4eull,
    0xd8210befd30efa5aull,
};
static UWtype pow5_bits_227[] = {
    0xdafd000000000000ull,
    0x2a0e5fdda70d39d6ull,
    0x56b9fb75cb3ee4c7ull,
    0x328e111fed9a3807ull,
    0x68be51a89017eba7ull,
    0x8484de37861e223eull,
    0x1da861232ad783a2ull,
    0x65acfaec34810a71ull,
    0x8714a775e3e95c78ull,
};
static UWtype pow5_bits_228[] = {
    0x91bc400000000000ull,
    0xf491f7d510d0884cull,
    0x2c687a533e0e9df8ull,
    0xff319567e900c609ull,
    0x2ede612b41de690ull,
    0x25a615c567a5aaceull,
    0x6512796bf58d648bull,
    0x7f1839a741a14d0dull,
    0xa8d9d1535ce3b396ull,
};
static UWtype pow5_bits_229[] = {
    0xb62b500000000000ull,
    0x31b675ca5504aa5full,
    0x778298e80d924577ull,
    0x3efdfac1e340f78bull,
    0x83a95f9761256035ull,
    0xef0f9b36c18f1581ull,
    0xbe5717c6f2f0bdadull,
    0x1ede48111209a050ull,
    0xd31045a8341ca07cull,
};
static UWtype pow5_bits_230[] = {
    0xd1db120000000000ull,
    0x7f12099e7522ea7bull,
    0x2ab19f91087b6b6aull,
    0x475ebcb92e089ab7ull,
    0xf249dbbe9cb75c21ull,
    0xb569c10238f96d70ull,
    0x76f66edc57d6768cull,
    0x934aed0aab460432ull,
    0x83ea2b892091e44dull,
};
static UWtype pow5_bits_231[] = {
    0xc651d68000000000ull,
    0x1ed68c06126ba51aull,
    0xf55e07754a9a4645ull,
    0x99366be7798ac164ull,
    0x2edc52ae43e53329ull,
    0xe2c43142c737c8cdull,
    0x14b40a936dcc142full,
    0xf81da84d5617853full,
    0xa4e4b66b68b65d60ull,
};
static UWtype pow5_bits_232[] = {
    0x77e64c2000000000ull,
    0x668c2f0797068e61ull,
    0x32b589529d40d7d6ull,
    0xff8406e157ed71beull,
    0x7a936759d4de7ff3ull,
    0xdb753d937905bb00ull,
    0xd9e10d38493f193bull,
    0x36251260ab9d668eull,
    0xce1de40642e3f4b9ull,
};
static UWtype pow5_bits_233[] = {
    0xeaefef9400000000ull,
    0x179d64be6418fcull,
    0xdfb175d3a24886e6ull,
    0x7fb2844cd6f46716ull,
    0x4c9c2098250b0ff8ull,
    0x6929467c2ba394e0ull,
    0x482ca8432dc76fc5ull,
    0xc1d72b7c6b426019ull,
    0x80d2ae83e9ce78f3ull,
};
static UWtype pow5_bits_234[] = {
    0x25abeb7900000000ull,
    0x801d84bdedfd1f3cull,
    0x979dd3488adaa89full,
    0x9f9f25600cb180dcull,
    0x5fc328be2e4dd3f6ull,
    0xc373981b368c7a18ull,
    0x9a37d253f9394bb6ull,
    0xb24cf65b8612f81full,
    0xa1075a24e4421730ull,
};
static UWtype pow5_bits_235[] = {
    0x2f16e65740000000ull,
    0x6024e5ed697c670bull,
    0xbd85481aad9152c7ull,
    0x4786eeb80fdde113ull,
    0x77b3f2edb9e148f4ull,
    0x74507e22042f989eull,
    0x80c5c6e8f7879ea4ull,
    0xdee033f26797b627ull,
    0xc94930ae1d529cfcull,
};
static UWtype pow5_bits_236[] = {
    0xfadc9fed10000000ull,
    0x382e1f68c3db80cdull,
    0xace69a2158f5a779ull,
    0x5968aa6613d55958ull,
    0x15a0efa928599b31ull,
    0x91649daa853b7ec6ull,
    0x60f738a33569864dull,
    0x169840ef017da3b1ull,
    0xfb9b7cd9a4a7443cull,
};
static UWtype pow5_bits_237[] = {
    0xbcc9e3f42a000000ull,
    0xc31cd3a17a693080ull,
    0x6c102054d79988abull,
    0xd7e16a7fcc6557d7ull,
    0xcd8495c9b93800feull,
    0x7adee28a93452f3bull,
    0xdc9a83660161f3f0ull,
    0x8e1f289560ee864eull,
    0x9d412e0806e88aa5ull,
};
static UWtype pow5_bits_238[] = {
    0xebfc5cf134800000ull,
    0xb3e40889d9037ca0ull,
    0x4714286a0d7fead6ull,
    0x8dd9c51fbf7eadcdull,
    0xc0e5bb3c2786013eull,
    0x99969b2d38167b0aull,
    0x93c1243f81ba70ecull,
    0xf1a6f2bab92a27e2ull,
    0xc491798a08a2ad4eull,
};
static UWtype pow5_bits_239[] = {
    0x26fb742d81a00000ull,
    0x60dd0aac4f445bc9ull,
    0x98d9328490dfe58cull,
    0x31503667af5e5940ull,
    0x711f2a0b3167818eull,
    0xbffc41f8861c19cdull,
    0x38b16d4f62290d27ull,
    0xae10af696774b1dbull,
    0xf5b5d7ec8acb58a2ull,
};
static UWtype pow5_bits_240[] = {
    0xb85d289c71040000ull,
    0xbc8a26abb18ab95dull,
    0x5f87bf92da8bef77ull,
    0xded22200cd9af7c8ull,
    0x66b37a46fee0b0f8ull,
    0xd7fda93b53d19020ull,
    0x36ee4519d59a838ull,
    0xacca6da1e0a8ef29ull,
    0x9991a6f3d6bf1765ull,
};
static UWtype pow5_bits_241[] = {
    0x267472c38d450000ull,
    0xabacb0569ded67b5ull,
    0x7769af77912eeb55ull,
    0x1686aa810101b5baull,
    0x806058d8be98dd37ull,
    0xdfd138a28c5f428ull,
    0x444a9d6604b01247ull,
    0x17fd090a58d32af3ull,
    0xbff610b0cc6edd3full,
};
static UWtype pow5_bits_242[] = {
    0x70118f7470964000ull,
    0x1697dc6c4568c1a2ull,
    0x15441b55757aa62bull,
    0xdc28552141422329ull,
    0xa0786f0eee3f1484ull,
    0xd17c586cb2f77132ull,
    0x155d44bf85dc16d8ull,
    0xddfc4b4cef07f5b0ull,
    0xeff394dcff8a948eull,
};
static UWtype pow5_bits_243[] = {
    0x860af9a8c65de800ull,
    0xee1ee9c3ab617905ull,
    0xad4a9115696ca7daull,
    0x9993534c8c955f9ull,
    0xa44b456954e76cd3ull,
    0x82edb743efdaa6bfull,
    0xd5a4af7b3a98e47ull,
    0x4abdaf101564f98eull,
    0x95f83d0a1fb69cd9ull,
};
static UWtype pow5_bits_244[] = {
    0xe78db812f7f56200ull,
    0xa9a6a4349639d746ull,
    0x189d355ac3c7d1d1ull,
    0xcbff8281fafbab78ull,
    0x8d5e16c3aa214807ull,
    0x63a92514ebd1506full,
    0x90b0ddb5a093f1d9ull,
    0x9d6d1ad41abe37f1ull,
    0xbb764c4ca7a4440full,
};
static UWtype pow5_bits_245[] = {
    0xa1712617b5f2ba80ull,
    0x14104d41bbc84d18ull,
    0x1ec482b174b9c646ull,
    0xbeff632279ba9656ull,
    0x70b59c7494a99a09ull,
    0xbc936e5a26c5a48bull,
    0xf4dd152308b8ee4full,
    0x84c86189216dc5edull,
    0xea53df5fd18d5513ull,
};
static UWtype pow5_bits_246[] = {
    0x64e6b7ced1b7b490ull,
    0xcc8a3049155d302full,
    0xd33ad1aee8f41bebull,
    0x175f9df58c149df5ull,
    0x267181c8dcea0046ull,
    0xd5dc24f8583b86d7ull,
    0xb90a2d35e57394f1ull,
    0x32fd3cf5b4e49bb4ull,
    0x92746b9be2f8552cull,
};
static UWtype pow5_bits_247[] = {
    0x3e2065c28625a1b4ull,
    0xbfacbc5b5ab47c3bull,
    0x4809861aa33122e6ull,
    0x9d378572ef19c573ull,
    0xf00de23b14248057ull,
    0x4b532e366e4a688cull,
    0xe74cb8835ed07a2eull,
    0x3fbc8c33221dc2a1ull,
    0xb7118682dbb66a77ull,
};
static UWtype pow5_bits_248[] = {
    0xda87f3327af0a21ull,
    0x6f97eb7231619b4aull,
    0x1a0be7a14bfd6ba0ull,
    0x848566cfaae036d0ull,
    0x2c115ac9d92da06dull,
    0xde27f9c409dd02b0ull,
    0x611fe6a4368498b9ull,
    0xfabaf3feaa5334aull,
    0xe4d5e82392a40515ull,
};
static UWtype pow5_bits_249[] = {
    0xa000000000000000ull,
    0x48894f7ff8cd6654ull,
    0x45bef3275edd010eull,
    0x104770c4cf7e6344ull,
    0x72d36041cacc2242ull,
    0x1b8ad8be27bc8444ull,
    0x2ad8fc1a862a21aeull,
    0x7cb3f026a212df74ull,
    0x29cb4d87f2a7400eull,
    0x8f05b1163ba6832dull,
};
static UWtype pow5_bits_250[] = {
    0xc800000000000000ull,
    0xdaaba35ff700bfe9ull,
    0x572eaff136944151ull,
    0x94594cf6035dfc15ull,
    0x8f8838523d7f2ad2ull,
    0xa26d8eedb1aba555ull,
    0x358f3b2127b4aa19ull,
    0x1be0ec304a979751ull,
    0x743e20e9ef511012ull,
    0xb2c71d5bca9023f8ull,
};
static UWtype pow5_bits_251[] = {
    0x3a00000000000000ull,
    0x51568c37f4c0efe4ull,
    0xacfa5bed843951a6ull,
    0x396fa03384357b1aull,
    0xf36a4666ccdef587ull,
    0xb08f2a91e168eaaull,
    0x82f309e971a1d4a0ull,
    0xa2d9273c5d3d7d25ull,
    0x914da9246b255416ull,
    0xdf78e4b2bd342cf6ull,
};
static UWtype pow5_bits_252[] = {
    0xa440000000000000ull,
    0xf2d617a2f8f895eeull,
    0xac1c797472a3d307ull,
    0x83e5c42032a16cf0ull,
    0xd8226c00400b5974ull,
    0x6e597a9b2ce192aull,
    0x71d7e631e70524e4ull,
    0x25c7b885ba466e37ull,
    0x1ad089b6c2f7548eull,
    0x8bab8eefb6409c1aull,
};
static UWtype pow5_bits_253[] = {
    0x4d50000000000000ull,
    0xef8b9d8bb736bb6aull,
    0xd72397d18f4cc7c9ull,
    0xa4df35283f49c82cull,
    0x8e2b0700500e2fd1ull,
    0x89efd941f819f75ull,
    0x4e4ddfbe60c66e1dull,
    0xaf39a6a728d809c5ull,
    0xa184ac2473b529b1ull,
    0xae9672aba3d0c320ull,
};
static UWtype pow5_bits_254[] = {
    0xe0a4000000000000ull,
    0x6b6e84eea5046a44ull,
    0xcec7dc5f31ff9bcull,
    0xe1702724f1c3a38ull,
    0xf1b5c8c06411bbc6ull,
    0x4ac6bcf927620752ull,
    0xa1e157adf8f809a4ull,
    0x1b081050f30e0c36ull,
    0xc9e5d72d90a2741eull,
    0xda3c0f568cc4f3e8ull,
};
static UWtype pow5_bits_255[] = {
    0xc66800000000000ull,
    0xc32513152722c26bull,
    0x813ce9bb7f3fc15ull,
    0xc8ce61877171a463ull,
    0xd7119d783e8b155bull,
    0xaebc361bb89d4493ull,
    0x252cd6ccbb9b0606ull,
    0xd0e50a3297e8c7a2ull,
    0x7e2fa67c7a658892ull,
    0x8865899617fb1871ull,
};
static UWtype pow5_bits_256[] = {
    0xcf80200000000000ull,
    0x33ee57da70eb7305ull,
    0xca18c242a5f0fb1bull,
    0xbb01f9e94dce0d7bull,
    0xccd604d64e2ddab2ull,
    0x5a6b43a2a6c495b8ull,
    0xae780c7fea81c788ull,
    0x851e4cbf3de2f98aull,
    0xddbb901b98feeab7ull,
    0xaa7eebfb9df9de8dull,
};
static UWtype pow5_bits_257[] = {
    0x4360280000000000ull,
    0xe9edd10d264fc7ull,
    0xbc9ef2d34f6d39e2ull,
    0x69c27863a14190daull,
    0xb860be1b9515full,
    0x7106148b5075bb27ull,
    0x5a160f9fe522396aull,
    0x6665dfef0d5bb7edull,
    0x552a74227f3ea565ull,
    0xd51ea6fa85785631ull,
};
static UWtype pow5_bits_258[] = {
    0x8a1c190000000000ull,
    0x409234a2a837f1dcull,
    0xb5e357c411a4442dull,
    0xa2198b3e44c8fa88ull,
    0x600733c76d13d2dbull,
    0x86a3ccd7124994f8ull,
    0x584dc9c3ef3563e2ull,
    0x5fffabf5685952f4ull,
    0xd53a88958f87275full,
    0x8533285c936b35deull,
};
static UWtype pow5_bits_259[] = {
    0xaca31f4000000000ull,
    0x90b6c1cb5245ee53ull,
    0xe35c2db5160d5538ull,
    0x8a9fee0dd5fb392aull,
    0x780900b94858c792ull,
    0x284cc00cd6dbfa36ull,
    0x6e613c34eb02bcdbull,
    0x37ff96f2c26fa7b1ull,
    0x8a892abaf368f137ull,
    0xa67ff273b8460356ull,
};
static UWtype pow5_bits_260[] = {
    0x97cbe71000000000ull,
    0xb4e4723e26d769e8ull,
    0x9c3339225b90aa86ull,
    0x2d47e9914b7a0775ull,
    0x160b40e79a6ef977ull,
    0xf25ff0100c92f8c4ull,
    0xc9f98b4225c36c11ull,
    0x5ff7caf730b919dull,
    0x2d2b7569b0432d85ull,
    0xd01fef10a657842cull,
};
static UWtype pow5_bits_261[] = {
    0x5edf706a00000000ull,
    0x310ec766d846a231ull,
    0x81a003b5793a6a94ull,
    0x7c4cf1facf2c44a9ull,
    0x8dc70890c0855beaull,
    0x377bf60a07dbdb7aull,
    0x9e3bf709579a238bull,
    0x23bfadeda7e73b02ull,
    0x9c3b29620e29fc73ull,
    0x8213f56a67f6b29bull,
};
static UWtype pow5_bits_262[] = {
    0xb6974c8480000000ull,
    0x3d5279408e584abdull,
    0xe20804a2d7890539ull,
    0x1b602e7982f755d3ull,
    0x3138cab4f0a6b2e5ull,
    0x55af38c89d2d259ull,
    0x45caf4cbad80ac6eull,
    0xecaf996911e109c3ull,
    0x8349f3ba91b47b8full,
    0xa298f2c501f45f42ull,
};
static UWtype pow5_bits_263[] = {
    0x243d1fa5a0000000ull,
    0x8ca71790b1ee5d6dull,
    0xda8a05cb8d6b4687ull,
    0x62383a17e3b52b48ull,
    0x7d86fd622cd05f9eull,
    0x86b1b06fac4786efull,
    0x173db1fe98e0d789ull,
    0xe7db7fc356594c34ull,
    0x241c70a936219a73ull,
    0xcb3f2f7642717713ull,
};
static UWtype pow5_bits_264[] = {
    0x6d4c678f08000000ull,
    0x6fd0dd74de69f4c8ull,
    0x112c873e70c61829ull,
    0xfac6489ddca2761bull,
    0x5ce8bcbab8047785ull,
    0xe85e1c8b975968abull,
    0x1d0d1e7e3f190d6bull,
    0xe1d25fb42bef9f41ull,
    0xed238cd383aa0110ull,
    0xfe0efb53d30dd4d7ull,
};
static UWtype pow5_bits_265[] = {
    0x444fc0b965000000ull,
    0xe5e28a690b0238fdull,
    0xeabbd487067bcf19ull,
    0xbcbbed62a9e589d0ull,
    0x1a1175f4b302cab3ull,
    0x713ad1d73e97e16bull,
    0xb228330ee76fa863ull,
    0x8d237bd09b75c388ull,
    0xf4363804324a40aaull,
    0x9ec95d1463e8a506ull,
};
static UWtype pow5_bits_266[] = {
    0x9563b0e7be400000ull,
    0x5f5b2d034dc2c73cull,
    0x256ac9a8c81ac2e0ull,
    0xabeae8bb545eec45ull,
    0xe095d371dfc37d60ull,
    0x4d89864d0e3dd9c5ull,
    0xdeb23fd2a14b927cull,
    0x306c5ac4c253346aull,
    0xb143c6053edcd0d5ull,
    0xc67bb4597ce2ce48ull,
};
static UWtype pow5_bits_267[] = {
    0xbabc9d21add00000ull,
    0x7731f8442133790bull,
    0x6ec57c12fa217398ull,
    0xd6e5a2ea2976a756ull,
    0x58bb484e57b45cb8ull,
    0x60ebe7e051cd5037ull,
    0x965ecfc7499e771bull,
    0x7c877175f2e80185ull,
    0xdd94b7868e94050aull,
    0xf81aa16fdc1b81daull,
};
static UWtype pow5_bits_268[] = {
    0x54b5e2350ca20000ull,
    0x4a7f3b2a94c02ba7ull,
    0x53b6d8bdc54e83full,
    0x864f85d259ea2896ull,
    0x97750d30f6d0b9f3ull,
    0x1c9370ec33205222ull,
    0x7dfb41dc8e030a71ull,
    0x8dd4a6e9b7d100f3ull,
    0xca7cf2b4191c8326ull,
    0x9b10a4e5e9913128ull,
};
static UWtype pow5_bits_269[] = {
    0x29e35ac24fca8000ull,
    0x1d1f09f539f03691ull,
    0x868a48eed36a224full,
    0x67e36746f064b2bbull,
    0x3d52507d3484e870ull,
    0x63b84d273fe866abull,
    0x5d7a1253b183cd0dull,
    0x3149d0a425c54130ull,
    0xfd1c2f611f63a3f0ull,
    0xc1d4ce1f63f57d72ull,
};
static UWtype pow5_bits_270[] = {
    0x745c3172e3bd2000ull,
    0xe466cc72886c4435ull,
    0x682cdb2a8844aae2ull,
    0x81dc4118ac7ddf6aull,
    0xca6e49c81a6228cull,
    0xbca660710fe28056ull,
    0x74d896e89de4c050ull,
    0x3d9c44cd2f36917cull,
    0xbc633b39673c8cecull,
    0xf24a01a73cf2dccfull,
};
static UWtype pow5_bits_271[] = {
    0x68b99ee7ce563400ull,
    0xcec03fc79543aaa1ull,
    0x811c08fa952aeacdull,
    0xd129a8af6bceaba2ull,
    0xc7e84ee1d107d597ull,
    0x75e7fc46a9ed9035ull,
    0xc9075e5162aef832ull,
    0xa681ab003d821aedull,
    0xd5be0503e085d813ull,
    0x976e41088617ca01ull,
};
static UWtype pow5_bits_272[] = {
    0xc2e806a1c1ebc100ull,
    0x42704fb97a949549ull,
    0x21630b393a75a581ull,
    0xc57412db46c2568bull,
    0x39e2629a4549cafdull,
    0x1361fb585468f443ull,
    0x3b4935e5bb5ab63full,
    0x902215c04ce2a1a9ull,
    0x4b2d8644d8a74e18ull,
    0xbd49d14aa79dbc82ull,
};
static UWtype pow5_bits_273[] = {
    0x33a2084a3266b140ull,
    0x930c63a7d939ba9cull,
    0xe9bbce0789130ee1ull,
    0x36d117921872ec2dull,
    0x85afb40d69c3dbdull,
    0xd83a7a2e69833154ull,
    0x8a1b835f2a3163ceull,
    0xb42a9b30601b4a13ull,
    0xddf8e7d60ed1219eull,
    0xec9c459d51852ba2ull,
};
static UWtype pow5_bits_274[] = {
    0xa045452e5f802ec8ull,
    0xfbe7be48e7c414a1ull,
    0xb21560c4b5abe94cull,
    0x4242aebb4f47d39cull,
    0x8538dd088621a696ull,
    0x47248c5d01f1fed4ull,
    0x3651321b7a5ede61ull,
    0x309aa0fe3c110e4cull,
    0xcabb90e5c942b503ull,
    0x93e1ab8252f33b45ull,
};
static UWtype pow5_bits_275[] = {
    0x8569679f7603a7aull,
    0x3ae1addb21b519caull,
    0xde9ab8f5e316e3a0ull,
    0xd2d35a6a2319c883ull,
    0xa687144aa7aa103bull,
    0x98edaf74426e7e89ull,
    0x43e57ea258f695f9ull,
    0xfcc1493dcb1551dfull,
    0x3d6a751f3b936243ull,
    0xb8da1662e7b00a17ull,
};
static UWtype pow5_bits_276[] = {
    0x8000000000000000ull,
    0x8a6c3c1875384918ull,
    0x499a1951ea22603cull,
    0xd64167335bdc9c88ull,
    0xc7883104abe03aa4ull,
    0x1028d95d5194944aull,
    0xff291b51530a1e2cull,
    0x14dede4aef343b77ull,
    0xfbf19b8d3ddaa657ull,
    0xcc512670a783ad4ull,
    0xe7109bfba19c0c9dull,
};
static UWtype pow5_bits_277[] = {
    0x5000000000000000ull,
    0xd683a58f49432dafull,
    0x2e004fd332557c25ull,
    0x5e8e0801969e1d5ull,
    0xbcb51ea2eb6c24a7ull,
    0x8a1987da52fcdcaeull,
    0xff79b112d3e652dbull,
    0x6d0b4aeed580a52aull,
    0x1d77013846a8a7f6ull,
    0x27fb2b80668b24c5ull,
    0x906a617d450187e2ull,
};
static UWtype pow5_bits_278[] = {
    0x2400000000000000ull,
    0x4c248ef31b93f91bull,
    0x798063c7feeadb2full,
    0xc76318a01fc45a4aull,
    0x6be2664ba6472dd0ull,
    0x6c9fe9d0e7bc13daull,
    0xbf581d5788dfe792ull,
    0x84e1daa8ae0ce75ull,
    0x64d4c1865852d1f4ull,
    0xb1f9f660802dedf6ull,
    0xb484f9dc9641e9daull,
};
static UWtype pow5_bits_279[] = {
    0xed00000000000000ull,
    0x1f2db2afe278f761ull,
    0x17e07cb9fea591fbull,
    0xf93bdec827b570ddull,
    0x6daffde8fd8f944ull,
    0x7c7e44521ab18d1ull,
    0x2f2e24ad6b17e177ull,
    0xa61a5152d990213ull,
    0xfe09f1e7ee678671ull,
    0x5e7873f8a0396973ull,
    0xe1a63853bbd26451ull,
};
static UWtype pow5_bits_280[] = {
    0x3420000000000000ull,
    0xf37c8faded8b9a9dull,
    0x2eec4df43f277b3cull,
    0x1bc56b3d18d1668aull,
    0xa448dfeb19e79bcbull,
    0x64dceeab350aef82ull,
    0xfd7cd6ec62eeeceaull,
    0xa67d072d3c7fa14bull,
    0x7ec63730f500b406ull,
    0xdb0b487b6423e1e8ull,
    0x8d07e33455637eb2ull,
};
static UWtype pow5_bits_281[] = {
    0x8128000000000000ull,
    0x305bb39968ee8144ull,
    0xbaa761714ef15a0cull,
    0xe2b6c60c5f05c02cull,
    0x4d5b17e5e06182bdull,
    0xfe142a56024dab63ull,
    0xfcdc0ca77baaa824ull,
    0x501c48f88b9f899eull,
    0x9e77c4fd3240e108ull,
    0x91ce1a9a3d2cda62ull,
    0xb049dc016abc5e5full,
};
static UWtype pow5_bits_282[] = {
    0xa172000000000000ull,
    0x3c72a07fc32a2195ull,
    0xe95139cda2adb08full,
    0x5b64778f76c73037ull,
    0x20b1dddf5879e36dull,
    0x3d9934eb82e1163cull,
    0xbc130fd15a95522eull,
    0x64235b36ae876c06ull,
    0x4615b63c7ed1194aull,
    0x7641a140cc7810fbull,
    0xdc5c5301c56b75f7ull,
};
static UWtype pow5_bits_283[] = {
    0x84e7400000000000ull,
    0x85c7a44fd9fa54fdull,
    0xf1d2c42085ac8e59ull,
    0x591ecab9aa3c7e22ull,
    0x946f2aab974c2e24ull,
    0xe67fc11331ccade5ull,
    0x358be9e2d89d535cull,
    0x7e9619022d14a384ull,
    0xbcd91e5cf42afceull,
    0xa9e904c87fcb0a9dull,
    0x89b9b3e11b6329baull,
};
static UWtype pow5_bits_284[] = {
    0xe621100000000000ull,
    0xe7398d63d078ea3cull,
    0xae477528a717b1efull,
    0x6f667d6814cb9dabull,
    0xf98af5567d1f39adull,
    0x201fb157fe3fd95eull,
    0x42eee45b8ec4a834ull,
    0x1e3b9f42b859cc65ull,
    0x4ec0f65f43135bc2ull,
    0x546345fa9fbdcd44ull,
    0xac2820d9623bf429ull,
};
static UWtype pow5_bits_285[] = {
    0x1fa9540000000000ull,
    0xe107f0bcc49724ccull,
    0x99d95272d0dd9e6bull,
    0xcb401cc219fe8516ull,
    0xb7edb2ac1c670818ull,
    0x28279dadfdcfcfb6ull,
    0x93aa9d727275d241ull,
    0xa5ca871366703f7eull,
    0x627133f713d832b2ull,
    0xa97c177947ad4095ull,
    0xd732290fbacaf133ull,
};
static UWtype pow5_bits_286[] = {
    0x93c9d48000000000ull,
    0x6ca4f675fade76ffull,
    0x2027d387c28a8303ull,
    0x7f0811f9503f132eull,
    0x32f48fab91c0650full,
    0xb918c28cbea1e1d2ull,
    0x1c4aa2678789a368ull,
    0xa79e946c200627afull,
    0x5d86c07a6c671fafull,
    0x49ed8eabcccc485dull,
    0x867f59a9d4bed6c0ull,
};
static UWtype pow5_bits_287[] = {
    0x78bc49a000000000ull,
    0x47ce3413799614bfull,
    0xa831c869b32d23c4ull,
    0x5eca1677a44ed7f9ull,
    0xbfb1b39676307e53ull,
    0xe75ef32fee4a5a46ull,
    0xe35d4b01696c0c42ull,
    0x918639872807b19aull,
    0xb4e870990780e79bull,
    0x5c68f256bfff5a74ull,
    0xa81f301449ee8c70ull,
};
static UWtype pow5_bits_288[] = {
    0x56eb5c0800000000ull,
    0x59c1c11857fb99efull,
    0x123e3a841ff86cb5ull,
    0x367c9c158d628df8ull,
    0x6f9e207c13bc9de8ull,
    0xa136affbe9dcf0d8ull,
    0x9c349dc1c3c70f53ull,
    0x75e7c7e8f2099e01ull,
    0xe2228cbf49612182ull,
    0x73832eec6fff3111ull,
    0xd226fc195c6a2f8cull,
};
static UWtype pow5_bits_289[] = {
    0x9653198500000000ull,
    0x581918af36fd4035ull,
    0xb66e49293fb43f1ull,
    0x220de18d785d98bbull,
    0x45c2d44d8c55e2b1ull,
    0x44c22dfd722a1687ull,
    0x1a0e2991a5c6994ull,
    0x89b0dcf1974602c1ull,
    0x2d5597f78ddcb4f1ull,
    0xc831fd53c5ff7eabull,
    0x83585d8fd9c25db7ull,
};
static UWtype pow5_bits_290[] = {
    0xfbe7dfe640000000ull,
    0xae1f5edb04bc9042ull,
    0xce409db738fa14edull,
    0x6a9159f0d674fee9ull,
    0x17338960ef6b5b5dull,
    0x55f2b97cceb49c29ull,
    0x42091b3f60f383f9ull,
    0xec1d142dfd178371ull,
    0xf8aafdf57153e22dull,
    0xba3e7ca8b77f5e55ull,
    0xa42e74f3d032f525ull,
};
static UWtype pow5_bits_291[] = {
    0xbae1d7dfd0000000ull,
    0x19a73691c5ebb453ull,
    0x41d0c52507389a29ull,
    0xc535b06d0c123ea4ull,
    0x5d006bb92b463234ull,
    0xab6f67dc0261c333ull,
    0x928b620f393064f7ull,
    0x672459397c5d644dull,
    0x76d5bd72cda8dab9ull,
    0x28ce1bd2e55f35ebull,
    0xcd3a1230c43fb26full,
};
static UWtype pow5_bits_292[] = {
    0x54cd26ebe2000000ull,
    0xb008821b1bb350b4ull,
    0xa9227b3724836059ull,
    0xfb418e44278b6726ull,
    0x1a204353bb0bdf60ull,
    0xcb25a0e9817d1a00ull,
    0x7b971d4983be3f1aull,
    0xe076b7c3edba5eb0ull,
    0x2a459667c08988b3ull,
    0x7980d163cf5b81b3ull,
    0x80444b5e7aa7cf85ull,
};
static UWtype pow5_bits_293[] = {
    0x6a0070a6da800000ull,
    0x1c0aa2a1e2a024e1ull,
    0x536b1a04eda43870ull,
    0x3a11f1d5316e40f0ull,
    0x20a85428a9ced739ull,
    0x7def0923e1dc6080ull,
    0x9a7ce49be4adcee1ull,
    0xd89465b4e928f65cull,
    0xf4d6fc01b0abeae0ull,
    0xd7e105bcc332621full,
    0xa0555e361951c366ull,
};
static UWtype pow5_bits_294[] = {
    0xc4808cd091200000ull,
    0x230d4b4a5b482e19ull,
    0x6845e086290d468cull,
    0x88966e4a7dc9d12cull,
    0x28d26932d4428d07ull,
    0xdd6acb6cda5378a0ull,
    0xc11c1dc2ddd94299ull,
    0xeb97f22237333f3ull,
    0xf20cbb021cd6e599ull,
    0x8dd9472bf3fefaa7ull,
    0xc86ab5c39fa63440ull,
};
static UWtype pow5_bits_295[] = {
    0x35a0b004b5680000ull,
    0x2bd09e1cf21a39a0ull,
    0x825758a7b350982full,
    0x6abc09dd1d3c4577ull,
    0x3307037f89533049ull,
    0x54c57e4810e856c8ull,
    0xb1632533954f9340ull,
    0x5267deeaac5000f0ull,
    0xee8fe9c2a40c9effull,
    0xb14f98f6f0feb951ull,
    0xfa856334878fc150ull,
};
static UWtype pow5_bits_296[] = {
    0x21846e02f1610000ull,
    0x7b6262d217506404ull,
    0xb1769768d0125f1dull,
    0xe2b5862a3245ab6aull,
    0x1fe4622fb5d3fe2dull,
    0x34fb6eed0a91363dull,
    0x6eddf7403d51bc08ull,
    0x9380eb52abb20096ull,
    0x3519f219a687e35full,
    0x6ed1bf9a569f33d3ull,
    0x9c935e00d4b9d8d2ull,
};
static UWtype pow5_bits_297[] = {
    0x29e58983adb94000ull,
    0xda3afb869d247d05ull,
    0x5dd43d430416f6e4ull,
    0x5b62e7b4bed71645ull,
    0x67dd7abba348fdb9ull,
    0x423a4aa84d3583ccull,
    0xa9575104ca62b0aull,
    0x78612627569e80bcull,
    0x2606ea01029dc37ull,
    0xa862f80ec4700c8ull,
    0xc3b8358109e84f07ull,
};
static UWtype pow5_bits_298[] = {
    0x745eebe499279000ull,
    0x10c9ba68446d9c46ull,
    0xb5494c93c51cb49eull,
    0xb23ba1a1ee8cdbd6ull,
    0x81d4d96a8c1b3d27ull,
    0xd2c8dd526082e4bfull,
    0xd3ad2545fcfb5ccull,
    0x56796fb12c4620ebull,
    0x2f88a4814345345ull,
    0xcd27bb612758c0faull,
    0xf4a642e14c6262c8ull,
};
static UWtype pow5_bits_299[] = {
    0x8bb536edfb8ba00ull,
    0xca7e14812ac481acull,
    0x314dcfdc5b31f0e2ull,
    0xcf65450535180966ull,
    0xb12507e297910638ull,
    0x3bd8a537c51cef7ull,
    0xe844c374bbe1d1a0ull,
    0x560be5cebbabd492ull,
    0x41db566d0ca0b40bull,
    0x8038d51cb897789cull,
    0x98e7e9cccfbd7dbdull,
};
static UWtype pow5_bits_300[] = {
    0xaea284a97a6e880ull,
    0x7d1d99a17575a217ull,
    0xbda143d371fe6d1bull,
    0x33e9646825e0bbfull,
    0x9d6e49db3d7547c7ull,
    0x4acece85b6642b5ull,
    0xa255f451eada4608ull,
    0x2b8edf426a96c9b7ull,
    0x52522c084fc8e10eull,
    0xe0470a63e6bd56c3ull,
    0xbf21e44003acdd2cull,
};
static UWtype pow5_bits_301[] = {
    0xcda4b25d3d90a2a0ull,
    0x5c650009d2d30a9cull,
    0xad0994c84e7e0862ull,
    0xc40e3bd822f58eafull,
    0x4c9dc520cd299b8ull,
    0x5d82822723fd363ull,
    0x8aeb71666590d78aull,
    0xb6729713053c7c25ull,
    0x26e6b70a63bb1951ull,
    0x1858ccfce06cac74ull,
    0xeeea5d5004981478ull,
};
static UWtype pow5_bits_302[] = {
    0x86ef7a467a65a4ull,
    0x79bf200623c3e6a2ull,
    0xcc25fcfd310ec53dull,
    0x7a88e56715d9792dull,
    0xe2fe29b34803a013ull,
    0x43a719158767e41dull,
    0x76d326dfff7a86b6ull,
    0x12079e6be345cd97ull,
    0x985032667e54efd3ull,
    0xf37801e0c43ebc8ull,
    0x95527a5202df0ccbull,
};
static UWtype pow5_bits_303[] = {
    0x80a8ab58d818ff0dull,
    0xd82ee807acb4e04aull,
    0x3f2f7c3c7d52768cull,
    0x592b1ec0db4fd779ull,
    0x5bbdb4201a048818ull,
    0xd490df5ae941dd25ull,
    0x5487f097ff592863ull,
    0xd6898606dc1740fdull,
    0xbe643f001dea2bc7ull,
    0xd30560258f54e6baull,
    0xbaa718e68396cffdull,
};
static UWtype pow5_bits_304[] = {
    0x4000000000000000ull,
    0x20d2d62f0e1f3ed0ull,
    0xe3aa20997e2185dull,
    0x8efb5b4b9ca71430ull,
    0x6f75e6711223cd57ull,
    0xb2ad21282085aa1eull,
    0xc9b51731a392546eull,
    0xa9a9ecbdff2f727cull,
    0xcc2be788931d113cull,
    0x6dfd4ec02564b6b9ull,
    0x47c6b82ef32a2069ull,
    0xe950df20247c83fdull,
};
static UWtype pow5_bits_305[] = {
    0x2800000000000000ull,
    0x3483c5dd68d38742ull,
    0x8e4a545feed4f3aull,
    0xb95d190f41e86c9eull,
    0x5a9b006ab566056ull,
    0x2fac34b914538a53ull,
    0xfe112e7f063b74c5ull,
    0xea0a33f6bf7da78dull,
    0x1f9b70b55bf22ac5ull,
    0xe4be5138175ef234ull,
    0x4cdc331d57fa5441ull,
    0x91d28b7416cdd27eull,
};
static UWtype pow5_bits_306[] = {
    0xb200000000000000ull,
    0xc1a4b754c3086912ull,
    0x8b1dce977ea8a308ull,
    0x67b45f53126287c5ull,
    0xc7141c08562bf86cull,
    0x7b9741e759686ce7ull,
    0x7d957a1ec7ca51f6ull,
    0x648cc0f46f5d1171ull,
    0x27824ce2b2eeb577ull,
    0x5dede5861d36aec1ull,
    0xe0133fe4adf8e952ull,
    0xb6472e511c81471dull,
};
static UWtype pow5_bits_307[] = {
    0x5e80000000000000ull,
    0xf20de529f3ca8357ull,
    0xede5423d5e52cbcaull,
    0x81a17727d6fb29b6ull,
    0xb8d9230a6bb6f687ull,
    0x1a7d12612fc28821ull,
    0xdcfad8a679bce674ull,
    0x3daff1318b3455cdull,
    0x7162e01b5faa62d5ull,
    0xf5695ee7a4845a71ull,
    0x58180fddd97723a6ull,
    0xe3d8f9e563a198e5ull,
};
static UWtype pow5_bits_308[] = {
    0x9b10000000000000ull,
    0xd748af3a385e9216ull,
    0x54af49665af3bf5eull,
    0xb104ea78e65cfa12ull,
    0x1387b5e683525a14ull,
    0x908e2b7cbdd99515ull,
    0xaa1cc7680c161008ull,
    0x468df6bef700b5a0ull,
    0xe6ddcc111bca7dc5ull,
    0x5961db50c6d2b886ull,
    0x570f09eaa7ea7648ull,
    0x8e679c2f5e44ff8full,
};
static UWtype pow5_bits_309[] = {
    0x41d4000000000000ull,
    0x8d1adb08c676369cull,
    0xe9db1bbff1b0af36ull,
    0xdd4625171ff43896ull,
    0x5869a3602426f099ull,
    0xb4b1b65bed4ffa5aull,
    0xd4a3f9420f1b940aull,
    0x9831746eb4c0e308ull,
    0xa0953f1562bd1d36ull,
    0x6fba5224f88766a8ull,
    0x2cd2cc6551e513daull,
    0xb201833b35d63f73ull,
};
static UWtype pow5_bits_310[] = {
    0x5249000000000000ull,
    0x306191caf813c443ull,
    0xa451e2afee1cdb04ull,
    0x5497ae5ce7f146bcull,
    0xee840c382d30acc0ull,
    0x61de23f2e8a3f8f0ull,
    0x9ccf79292e2790dull,
    0x3e3dd18a61f11bcbull,
    0xc8ba8edabb6c6484ull,
    0xba8e6ae36a94052ull,
    0xf8077f7ea65e58d1ull,
    0xde81e40a034bcf4full,
};
static UWtype pow5_bits_311[] = {
    0x136da00000000000ull,
    0x9e3cfb1edb0c5aaaull,
    0xe6b32dadf4d208e2ull,
    0x34deccfa10f6cc35ull,
    0x951287a31c3e6bf8ull,
    0x5d2ad677d1667b96ull,
    0xe6201abb9bcd8ba8ull,
    0xa6e6a2f67d36b15eull,
    0xbd749948b523bed2ull,
    0xa749902ce229c833ull,
    0xfb04afaf27faf782ull,
    0x8b112e86420f6191ull,
};
static UWtype pow5_bits_312[] = {
    0x9849080000000000ull,
    0x45cc39e691cf7154ull,
    0x605ff91972068b1bull,
    0x4216803895347f43ull,
    0x3a57298be34e06f6ull,
    0x74758c15c5c01a7cull,
    0x9fa8216a82c0ee92ull,
    0x50a04bb41c845db6ull,
    0xacd1bf9ae26cae87ull,
    0x511bf4381ab43a40ull,
    0x79c5db9af1f9b563ull,
    0xadd57a27d29339f6ull,
};
static UWtype pow5_bits_313[] = {
    0xbe5b4a0000000000ull,
    0x173f486036434da9ull,
    0x3877f75fce882de2ull,
    0xd29c2046ba819f14ull,
    0x48ecf3eedc2188b3ull,
    0x1192ef1b3730211bull,
    0x479229c523712a37ull,
    0x24c85ea123a57524ull,
    0xd8062f819b07da29ull,
    0x2562f146216148d0ull,
    0x18375281ae7822bcull,
    0xd94ad8b1c7380874ull,
};
static UWtype pow5_bits_314[] = {
    0x16f90e4000000000ull,
    0x4e878d3c21ea108aull,
    0xa34afa9be1151cadull,
    0x63a1942c3491036cull,
    0xd9418754994f570ull,
    0x6afbd571027e14b1ull,
    0xacbb5a1b3626ba62ull,
    0xb6fd3b24b6476936ull,
    0x8703ddb100e4e859ull,
    0x975dd6cbd4dccd82ull,
    0x8f2293910d0b15b5ull,
    0x87cec76f1c830548ull,
};
static UWtype pow5_bits_315[] = {
    0x9cb751d000000000ull,
    0xa229708b2a6494acull,
    0xcc1db942d95a63d8ull,
    0x7c89f93741b54447ull,
    0x50f91e929bfa32ccull,
    0x5bacacd431d99ddull,
    0x57ea30a203b068fbull,
    0x24bc89ede3d94384ull,
    0x28c4d51d411e2270ull,
    0xfd354c7eca1400e3ull,
    0xb2eb3875504ddb22ull,
    0xa9c2794ae3a3c69aull,
};
static UWtype pow5_bits_316[] = {
    0xc3e5264400000000ull,
    0xcab3ccadf4fdb9d7ull,
    0xbf2527938fb0fcceull,
    0x9bac778512229559ull,
    0xa537663742f8bf7full,
    0xc7297d8093e50054ull,
    0x6de4bcca849c8339ull,
    0x2debac695ccf9465ull,
    0xf2f60a649165ab0cull,
    0xbc829f9e7c99011bull,
    0x5fa60692a46151ebull,
    0xd433179d9c8cb841ull,
};
static UWtype pow5_bits_317[] = {
    0xda6f37ea80000000ull,
    0x3eb05fecb91e9426ull,
    0x177738bc39ce9e01ull,
    0xc14bcab32b559d58ull,
    0xe7429fe289db77afull,
    0x1c79ee705c6f2034ull,
    0x64aef5fe92e1d204ull,
    0x9cb34bc1da01bcbfull,
    0x77d9c67edadf8ae7ull,
    0x55d1a3c30ddfa0b1ull,
    0xdbc7c41ba6bcd333ull,
    0x849feec281d7f328ull,
};
static UWtype pow5_bits_318[] = {
    0x910b05e520000000ull,
    0x8e5c77e7e7663930ull,
    0x1d5506eb48424581ull,
    0xb19ebd5ff62b04aeull,
    0x211347db2c52559bull,
    0x23986a0c738ae842ull,
    0x3ddab37e379a4685ull,
    0x83e01eb250822befull,
    0xd5d0381e91976da1ull,
    0x2b460cb3d15788ddull,
    0x12b9b522906c0800ull,
    0xa5c7ea73224deff3ull,
};
static UWtype pow5_bits_319[] = {
    0xb54dc75e68000000ull,
    0xf1f395e1e13fc77cull,
    0xa4aa48a61a52d6e1ull,
    0x9e066cb7f3b5c5d9ull,
    0xa95819d1f766eb02ull,
    0x6c7e848f906da252ull,
    0xd51605dc580d826ull,
    0xe4d8265ee4a2b6ebull,
    0x4b44462635fd4909ull,
    0x36178fe0c5ad6b15ull,
    0xd768226b34870a00ull,
    0xcf39e50feae16befull,
};
static UWtype pow5_bits_320[] = {
    0xf1509c9b01000000ull,
    0x37383dad2cc7dcadull,
    0x6ea6d67d073c64dull,
    0xa2c403f2f8519ba8ull,
    0xa9d710233aa052e1ull,
    0x3cf12d9ba448573ull,
    0xe852dc3a9b708718ull,
    0x2f0717fb4ee5b252ull,
    0x4f0aabd7e1be4da6ull,
    0x21ceb9ec7b8c62edull,
    0xe6a1158300d46640ull,
    0x81842f29f2cce375ull,
};
static UWtype pow5_bits_321[] = {
    0x6da4c3c1c1400000ull,
    0x85064d1877f9d3d9ull,
    0x8a508c1c490b7e0ull,
    0xb7504efb6660292ull,
    0x944cd42c0948679aull,
    0x4c2d79028d5a6d0ull,
    0xa2679349424ca8deull,
    0xbac8ddfa229f1ee7ull,
    0xa2cd56cdda2de10full,
    0x2a4268679a6f7ba8ull,
    0x60495ae3c1097fd0ull,
    0xa1e53af46f801c53ull,
};
static UWtype pow5_bits_322[] = {
    0xc90df4b231900000ull,
    0xa647e05e95f848cfull,
    0x8ace4af235b4e5d8ull,
    0x8e52462ba3ff8336ull,
    0xb96009370b9a8180ull,
    0x85f38d74330b1084ull,
    0x8b01781b92dfd315ull,
    0xa97b1578ab46e6a1ull,
    0xcb80ac8150b95953ull,
    0x34d30281810b5a92ull,
    0x385bb19cb14bdfc4ull,
    0xca5e89b18b602368ull,
};
static UWtype pow5_bits_323[] = {
    0xbb5171debdf40000ull,
    0xcfd9d8763b765b03ull,
    0x2d81ddaec3221f4eull,
    0xb1e6d7b68cff6404ull,
    0xe7b80b84ce8121e0ull,
    0xe77070d13fcdd4a5ull,
    0xedc1d6227797c7daull,
    0x93d9dad6d618a049ull,
    0x7e60d7a1a4e7afa8ull,
    0x4207c321e14e3137ull,
    0x46729e03dd9ed7b5ull,
    0xfcf62c1dee382c42ull,
};
static UWtype pow5_bits_324[] = {
    0x5512e72b36b88000ull,
    0x41e82749e529f8e2ull,
    0x9c712a8d39f55391ull,
    0x6f3046d2181f9e82ull,
    0xb0d307330110b52cull,
    0xd0a64682c7e0a4e7ull,
    0x349925d58abedce8ull,
    0x5c6828c645cf642eull,
    0xaefc86c50710cdc9ull,
    0x4944d9f52cd0dec2ull,
    0x6c07a2c26a8346d1ull,
    0x9e19db92b4e31ba9ull,
};
static UWtype pow5_bits_325[] = {
    0xea57a0f60466a000ull,
    0x9262311c5e74771aull,
    0x438d75308872a875ull,
    0x8afc58869e278623ull,
    0x9d07c8ffc154e277ull,
    0x4cfd82379d8ce21ull,
    0xc1bf6f4aed6e9423ull,
    0xb38232f7d7433d39ull,
    0x5abba87648d5013bull,
    0x9b96107278051673ull,
    0xc7098b7305241885ull,
    0xc5a05277621be293ull,
};
static UWtype pow5_bits_326[] = {
    0xa4ed893385804800ull,
    0xf6fabd63761194e1ull,
    0x1470d27caa8f5292ull,
    0x6dbb6ea845b167acull,
    0x449bb3fb1aa1b15ull,
    0xc603ce2c584f01aaull,
    0x322f4b1da8ca392bull,
    0xa062bfb5cd140c88ull,
    0x316a9293db0a418aull,
    0x27b948f16065c10ull,
    0xb8cbee4fc66d1ea7ull,
    0xf70867153aa2db38ull,
};
static UWtype pow5_bits_327[] = {
    0x71475c033702d00ull,
    0xda5cb65e29cafd0dull,
    0x8cc6838dea99939bull,
    0x649525292b8ee0cbull,
    0x42ae1507cf0a50edull,
    0x5bc260dbb731610aull,
    0x1f5d8ef2897e63bbull,
    0xa43db7d1a02c87d5ull,
    0x1ee29b9c68e668f6ull,
    0x618d3cd96dc3f98aull,
    0x737f74f1dc043328ull,
    0x9a65406d44a5c903ull,
};
static UWtype pow5_bits_328[] = {
    0x48d99330404c3840ull,
    0xd0f3e3f5b43dbc50ull,
    0x6ff82471653ff882ull,
    0xbdba6e73767298feull,
    0xd3599a49c2cce528ull,
    0x32b2f912a4fdb94cull,
    0x6734f2af2bddfcaaull,
    0x4d4d25c60837a9caull,
    0xa69b428383200334ull,
    0x79f08c0fc934f7ecull,
    0x505f522e53053ff2ull,
    0xc0fe908895cf3b44ull,
};
static UWtype pow5_bits_329[] = {
    0x5b0ff7fc505f4650ull,
    0x8530dcf3214d2b64ull,
    0xbf62d8dbe8ff6a3ull,
    0xed290a10540f3f3eull,
    0x83000dc33801e72ull,
    0xbf5fb7574e3d27a0ull,
    0x1022f5af6d57bd4ull,
    0x60a06f378a45943dull,
    0xd042132463e80401ull,
    0x186caf13bb8235e7ull,
    0x647726b9e7c68fefull,
    0xf13e34aabb430a15ull,
};
static struct pow5 {
    int nBits; // Nubmer of bits in p^n
    int nWordsL;
    UWtype *bBitsML;
    UWtype bBitsDL[2];
} pow5[] = {
    /* 0 */ { 1, 1, pow5_bits_0, {0x0ull, 0x8000000000000000ull}},
    /* 1 */ { 3, 1, pow5_bits_1, {0xccccccccccccccccull, 0xccccccccccccccccull}},
    /* 2 */ { 5, 1, pow5_bits_2, {0x3d70a3d70a3d70a3ull, 0xa3d70a3d70a3d70aull}},
    /* 3 */ { 7, 1, pow5_bits_3, {0x645a1cac083126e9ull, 0x83126e978d4fdf3bull}},
    /* 4 */ { 10, 1, pow5_bits_4, {0xd3c36113404ea4a8ull, 0xd1b71758e219652bull}},
    /* 5 */ { 12, 1, pow5_bits_5, {0xfcf80dc33721d53ull, 0xa7c5ac471b478423ull}},
    /* 6 */ { 14, 1, pow5_bits_6, {0xa63f9a49c2c1b10full, 0x8637bd05af6c69b5ull}},
    /* 7 */ { 17, 1, pow5_bits_7, {0x3d32907604691b4cull, 0xd6bf94d5e57a42bcull}},
    /* 8 */ { 19, 1, pow5_bits_8, {0xfdc20d2b36ba7c3dull, 0xabcc77118461cefcull}},
    /* 9 */ { 21, 1, pow5_bits_9, {0x31680a88f8953030ull, 0x89705f4136b4a597ull}},
    /* 10 */ { 24, 1, pow5_bits_10, {0xb573440e5a884d1bull, 0xdbe6fecebdedd5beull}},
    /* 11 */ { 26, 1, pow5_bits_11, {0xf78f69a51539d748ull, 0xafebff0bcb24aafeull}},
    /* 12 */ { 28, 1, pow5_bits_12, {0xf93f87b7442e45d3ull, 0x8cbccc096f5088cbull}},
    /* 13 */ { 31, 1, pow5_bits_13, {0x2865a5f206b06fb9ull, 0xe12e13424bb40e13ull}},
    /* 14 */ { 33, 1, pow5_bits_14, {0x538484c19ef38c94ull, 0xb424dc35095cd80full}},
    /* 15 */ { 35, 1, pow5_bits_15, {0xf9d37014bf60a10ull, 0x901d7cf73ab0acd9ull}},
    /* 16 */ { 38, 1, pow5_bits_16, {0x4c2ebe687989a9b3ull, 0xe69594bec44de15bull}},
    /* 17 */ { 40, 1, pow5_bits_17, {0x9befeb9fad487c2ull, 0xb877aa3236a4b449ull}},
    /* 18 */ { 42, 1, pow5_bits_18, {0x3aff322e62439fcfull, 0x9392ee8e921d5d07ull}},
    /* 19 */ { 45, 1, pow5_bits_19, {0x2b31e9e3d06c32e5ull, 0xec1e4a7db69561a5ull}},
    /* 20 */ { 47, 1, pow5_bits_20, {0x88f4bb1ca6bcf584ull, 0xbce5086492111aeaull}},
    /* 21 */ { 49, 1, pow5_bits_21, {0xd3f6fc16ebca5e03ull, 0x971da05074da7beeull}},
    /* 22 */ { 52, 1, pow5_bits_22, {0x5324c68b12dd6338ull, 0xf1c90080baf72cb1ull}},
    /* 23 */ { 54, 1, pow5_bits_23, {0x75b7053c0f178293ull, 0xc16d9a0095928a27ull}},
    /* 24 */ { 56, 1, pow5_bits_24, {0xc4926a9672793542ull, 0x9abe14cd44753b52ull}},
    /* 25 */ { 59, 1, pow5_bits_25, {0x3a83ddbd83f52204ull, 0xf79687aed3eec551ull}},
    /* 26 */ { 61, 1, pow5_bits_26, {0x95364afe032a819dull, 0xc612062576589ddaull}},
    /* 27 */ { 63, 1, pow5_bits_27, {0x775ea264cf55347dull, 0x9e74d1b791e07e48ull}},
    /* 28 */ { 66, 2, pow5_bits_28, {0x8bca9d6e188853fcull, 0xfd87b5f28300ca0dull}},
    /* 29 */ { 68, 2, pow5_bits_29, {0x96ee45813a04330ull, 0xcad2f7f5359a3b3eull}},
    /* 30 */ { 70, 2, pow5_bits_30, {0xa1258379a94d028dull, 0xa2425ff75e14fc31ull}},
    /* 31 */ { 72, 2, pow5_bits_31, {0x80eacf948770ced7ull, 0x81ceb32c4b43fcf4ull}},
    /* 32 */ { 75, 2, pow5_bits_32, {0x67de18eda5814af2ull, 0xcfb11ead453994baull}},
    /* 33 */ { 77, 2, pow5_bits_33, {0xecb1ad8aeacdd58eull, 0xa6274bbdd0fadd61ull}},
    /* 34 */ { 79, 2, pow5_bits_34, {0xbd5af13bef0b113eull, 0x84ec3c97da624ab4ull}},
    /* 35 */ { 82, 2, pow5_bits_35, {0x955e4ec64b44e864ull, 0xd4ad2dbfc3d07787ull}},
    /* 36 */ { 84, 2, pow5_bits_36, {0xdde50bd1d5d0b9e9ull, 0xaa242499697392d2ull}},
    /* 37 */ { 86, 2, pow5_bits_37, {0x7e50d64177da2e54ull, 0x881cea14545c7575ull}},
    /* 38 */ { 89, 2, pow5_bits_38, {0x96e7bd358c904a21ull, 0xd9c7dced53c72255ull}},
    /* 39 */ { 91, 2, pow5_bits_39, {0xabec975e0a0d081aull, 0xae397d8aa96c1b77ull}},
    /* 40 */ { 93, 2, pow5_bits_40, {0x2323ac4b3b3da015ull, 0x8b61313bbabce2c6ull}},
    /* 41 */ { 96, 2, pow5_bits_41, {0x6b6c46dec52f6688ull, 0xdf01e85f912e37a3ull}},
    /* 42 */ { 98, 2, pow5_bits_42, {0x55f038b237591ed3ull, 0xb267ed1940f1c61cull}},
    /* 43 */ { 100, 2, pow5_bits_43, {0x77f3608e92adb242ull, 0x8eb98a7a9a5b04e3ull}},
    /* 44 */ { 103, 2, pow5_bits_44, {0x8cb89a7db77c506aull, 0xe45c10c42a2b3b05ull}},
    /* 45 */ { 105, 2, pow5_bits_45, {0x3d607b97c5fd0d22ull, 0xb6b00d69bb55c8d1ull}},
    /* 46 */ { 107, 2, pow5_bits_46, {0xcab3961304ca70e8ull, 0x9226712162ab070dull}},
    /* 47 */ { 110, 2, pow5_bits_47, {0xaab8f01e6e10b4a6ull, 0xe9d71b689dde71afull}},
    /* 48 */ { 112, 2, pow5_bits_48, {0x5560c018580d5d52ull, 0xbb127c53b17ec159ull}},
    /* 49 */ { 114, 2, pow5_bits_49, {0xdde7001379a44aa8ull, 0x95a8637627989aadull}},
    /* 50 */ { 117, 2, pow5_bits_50, {0x963e66858f6d4440ull, 0xef73d256a5c0f77cull}},
    /* 51 */ { 119, 2, pow5_bits_51, {0xde98520472bdd033ull, 0xbf8fdb78849a5f96ull}},
    /* 52 */ { 121, 2, pow5_bits_52, {0xe546a8038efe4029ull, 0x993fe2c6d07b7fabull}},
    /* 53 */ { 124, 2, pow5_bits_53, {0xd53dd99f4b3066a8ull, 0xf53304714d9265dfull}},
    /* 54 */ { 126, 2, pow5_bits_54, {0xaa97e14c3c26b886ull, 0xc428d05aa4751e4cull}},
    /* 55 */ { 128, 2, pow5_bits_55, {0x55464dd69685606bull, 0x9ced737bb6c4183dull}},
    /* 56 */ { 131, 3, pow5_bits_56, {0xeed6e2f0f0d56712ull, 0xfb158592be068d2eull}},
    /* 57 */ { 133, 3, pow5_bits_57, {0xf245825a5a445275ull, 0xc8de047564d20a8bull}},
    /* 58 */ { 135, 3, pow5_bits_58, {0x5b6aceaeae9d0ec4ull, 0xa0b19d2ab70e6ed6ull}},
    /* 59 */ { 137, 3, pow5_bits_59, {0xe2bbd88bbee40bd0ull, 0x808e17555f3ebf11ull}},
    /* 60 */ { 140, 3, pow5_bits_60, {0x3792f412cb06794dull, 0xcdb02555653131b6ull}},
    /* 61 */ { 142, 3, pow5_bits_61, {0x5fa8c3423c052dd7ull, 0xa48ceaaab75a8e2bull}},
    /* 62 */ { 144, 3, pow5_bits_62, {0x1953cf68300424acull, 0x83a3eeeef9153e89ull}},
    /* 63 */ { 147, 3, pow5_bits_63, {0x8eec7f0d19a03aadull, 0xd29fe4b18e88640eull}},
    /* 64 */ { 149, 3, pow5_bits_64, {0x3f2398d747b36224ull, 0xa87fea27a539e9a5ull}},
    /* 65 */ { 151, 3, pow5_bits_65, {0x98e947129fc2b4e9ull, 0x86ccbb52ea94baeaull}},
    /* 66 */ { 154, 3, pow5_bits_66, {0x5b0ed81dcc6abb0full, 0xd7adf884aa879177ull}},
    /* 67 */ { 156, 3, pow5_bits_67, {0xe272467e3d222f3full, 0xac8b2d36eed2dac5ull}},
    /* 68 */ { 158, 3, pow5_bits_68, {0x1b8e9ecb641b58ffull, 0x8a08f0f8bf0f156bull}},
    /* 69 */ { 161, 3, pow5_bits_69, {0xf8e431456cf88e65ull, 0xdcdb1b2798182244ull}},
    /* 70 */ { 163, 3, pow5_bits_70, {0x2d835a9df0c6d851ull, 0xb0af48ec79ace837ull}},
    /* 71 */ { 165, 3, pow5_bits_71, {0x579c487e5a38ad0eull, 0x8d590723948a535full}},
    /* 72 */ { 168, 3, pow5_bits_72, {0x25c6da63c38de1b0ull, 0xe2280b6c20dd5232ull}},
    /* 73 */ { 170, 3, pow5_bits_73, {0x1e38aeb6360b1af3ull, 0xb4ecd5f01a4aa828ull}},
    /* 74 */ { 172, 3, pow5_bits_74, {0xb1c6f22b5e6f48c2ull, 0x90bd77f3483bb9b9ull}},
    /* 75 */ { 175, 3, pow5_bits_75, {0xb60b1d1230b20e04ull, 0xe7958cb87392c2c2ull}},
    /* 76 */ { 177, 3, pow5_bits_76, {0xf808e40e8d5b3e69ull, 0xb94470938fa89bceull}},
    /* 77 */ { 179, 3, pow5_bits_77, {0xf9a0b6720aaf6521ull, 0x9436c0760c86e30bull}},
    /* 78 */ { 182, 3, pow5_bits_78, {0x290123e9aab23b68ull, 0xed246723473e3813ull}},
    /* 79 */ { 184, 3, pow5_bits_79, {0x5400e987bbc1c920ull, 0xbdb6b8e905cb600full}},
    /* 80 */ { 186, 3, pow5_bits_80, {0xdccd879fc967d41aull, 0x97c560ba6b0919a5ull}},
    /* 81 */ { 189, 3, pow5_bits_81, {0xfae27299423fb9c3ull, 0xf2d56790ab41c2a2ull}},
    /* 82 */ { 191, 3, pow5_bits_82, {0xfbe85badce996168ull, 0xc24452da229b021bull}},
    /* 83 */ { 193, 4, pow5_bits_83, {0xc986afbe3ee11abaull, 0x9b69dbe1b548ce7cull}},
    /* 84 */ { 196, 4, pow5_bits_84, {0x75a44c6397ce912aull, 0xf8a95fcf88747d94ull}},
    /* 85 */ { 198, 4, pow5_bits_85, {0x91503d1c79720dbbull, 0xc6ede63fa05d3143ull}},
    /* 86 */ { 200, 4, pow5_bits_86, {0xdd9ca7d2df4d7c9ull, 0x9f24b832e6b0f436ull}},
    /* 87 */ { 203, 4, pow5_bits_87, {0xe2f610c84987bfa8ull, 0xfea126b7d78186bcull}},
    /* 88 */ { 205, 4, pow5_bits_88, {0x4f2b40a03ad2ffb9ull, 0xcbb41ef979346bcaull}},
    /* 89 */ { 207, 4, pow5_bits_89, {0x728900802f0f32faull, 0xa2f67f2dfa90563bull}},
    /* 90 */ { 209, 4, pow5_bits_90, {0x8ed400668c0c28c8ull, 0x825ecc24c873782full}},
    /* 91 */ { 212, 4, pow5_bits_91, {0x7e2000a41346a7a7ull, 0xd097ad07a71f26b2ull}},
    /* 92 */ { 214, 4, pow5_bits_92, {0xcb4ccd500f6bb952ull, 0xa6dfbd9fb8e5b88eull}},
    /* 93 */ { 216, 4, pow5_bits_93, {0x6f70a4400c562ddbull, 0x857fcae62d8493a5ull}},
    /* 94 */ { 219, 4, pow5_bits_94, {0x4be76d3346f0495full, 0xd59944a37c0752a2ull}},
    /* 95 */ { 221, 4, pow5_bits_95, {0xd652bdc29f26a119ull, 0xaae103b5fcd2a881ull}},
    /* 96 */ { 223, 4, pow5_bits_96, {0x11dbcb0218ebb414ull, 0x88b402f7fd75539bull}},
    /* 97 */ { 226, 4, pow5_bits_97, {0xe95fab368e45ecedull, 0xdab99e59958885c4ull}},
    /* 98 */ { 228, 4, pow5_bits_98, {0xede622920b6b23f1ull, 0xaefae51477a06b03ull}},
    /* 99 */ { 230, 4, pow5_bits_99, {0x57eb4edb3c55b65aull, 0x8bfbea76c619ef36ull}},
    /* 100 */ { 233, 4, pow5_bits_100, {0x59787e2b93bc56f7ull, 0xdff9772470297ebdull}},
    /* 101 */ { 235, 4, pow5_bits_101, {0x47939822dc96abf9ull, 0xb32df8e9f3546564ull}},
    /* 102 */ { 237, 4, pow5_bits_102, {0x9fa946824a12232dull, 0x8f57fa54c2a9eab6ull}},
    /* 103 */ { 240, 4, pow5_bits_103, {0xcc420a6a101d0515ull, 0xe55990879ddcaabdull}},
    /* 104 */ { 242, 4, pow5_bits_104, {0x9ce6ebb40173744ull, 0xb77ada0617e3bbcbull}},
    /* 105 */ { 244, 4, pow5_bits_105, {0x3b0b8bc90012929dull, 0x92c8ae6b464fc96full}},
    /* 106 */ { 247, 4, pow5_bits_106, {0x2b45ac74ccea842eull, 0xeadab0aba3b2dbe5ull}},
    /* 107 */ { 249, 4, pow5_bits_107, {0x890489f70a55368bull, 0xbbe226efb628afeaull}},
    /* 108 */ { 251, 4, pow5_bits_108, {0x3a6a07f8d510f86full, 0x964e858c91ba2655ull}},
    /* 109 */ { 254, 4, pow5_bits_109, {0x5d767327bb4e5a4cull, 0xf07da27a82c37088ull}},
    /* 110 */ { 256, 4, pow5_bits_110, {0xe45ec2862f71e1d6ull, 0xc06481fb9bcf8d39ull}},
    /* 111 */ { 258, 5, pow5_bits_111, {0x504bced1bf8e4e45ull, 0x99ea0196163fa42eull}},
    /* 112 */ { 261, 5, pow5_bits_112, {0x4d4617b5ff4a16d5ull, 0xf64335bcf065d37dull}},
    /* 113 */ { 263, 5, pow5_bits_113, {0xa9e795e65d4df11ull, 0xc5029163f384a931ull}},
    /* 114 */ { 265, 5, pow5_bits_114, {0xd54b944b84aa4c0dull, 0x9d9ba7832936edc0ull}},
    /* 115 */ { 268, 5, pow5_bits_115, {0xbbac2078d443ace2ull, 0xfc2c3f3841f17c67ull}},
    /* 116 */ { 270, 5, pow5_bits_116, {0xfc89b393dd02f0b5ull, 0xc9bcff6034c13052ull}},
    /* 117 */ { 272, 5, pow5_bits_117, {0xca07c2dcb0cf26f7ull, 0xa163ff802a3426a8ull}},
    /* 118 */ { 274, 5, pow5_bits_118, {0x806357d5a3f525full, 0x811ccc668829b887ull}},
    /* 119 */ { 277, 5, pow5_bits_119, {0x733d226229feea32ull, 0xce947a3da6a9273eull}},
    /* 120 */ { 279, 5, pow5_bits_120, {0xc2974eb4ee658828ull, 0xa54394fe1eedb8feull}},
    /* 121 */ { 281, 5, pow5_bits_121, {0xcedf722a585139baull, 0x843610cb4bf160cbull}},
    /* 122 */ { 284, 5, pow5_bits_122, {0x4aff1d108d4ec2c3ull, 0xd389b47879823479ull}},
    /* 123 */ { 286, 5, pow5_bits_123, {0xd598e40d3dd89bcfull, 0xa93af6c6c79b5d2dull}},
    /* 124 */ { 288, 5, pow5_bits_124, {0x11471cd764ad4972ull, 0x87625f056c7c4a8bull}},
    /* 125 */ { 291, 5, pow5_bits_125, {0xe871c7bf077ba8b7ull, 0xd89d64d57a607744ull}},
    /* 126 */ { 293, 5, pow5_bits_126, {0x86c16c98d2c953c6ull, 0xad4ab7112eb3929dull}},
    /* 127 */ { 295, 5, pow5_bits_127, {0x6bcdf07a423aa96bull, 0x8aa22c0dbef60ee4ull}},
    /* 128 */ { 298, 5, pow5_bits_128, {0xac7cb3f6d05ddbdeull, 0xddd0467c64bce4a0ull}},
    /* 129 */ { 300, 5, pow5_bits_129, {0xbd308ff8a6b17cb2ull, 0xb1736b96b6fd83b3ull}},
    /* 130 */ { 302, 5, pow5_bits_130, {0xca8d3ffa1ef463c1ull, 0x8df5efabc5979c8full}},
    /* 131 */ { 305, 5, pow5_bits_131, {0x10e1fff697ed6c69ull, 0xe3231912d5bf60e6ull}},
    /* 132 */ { 307, 5, pow5_bits_132, {0xd819992132456baull, 0xb5b5ada8aaff80b8ull}},
    /* 133 */ { 309, 5, pow5_bits_133, {0xace1474dc1d122eull, 0x915e2486ef32cd60ull}},
    /* 134 */ { 312, 5, pow5_bits_134, {0x77b020baf9c81d17ull, 0xe896a0d7e51e1566ull}},
    /* 135 */ { 314, 5, pow5_bits_135, {0x92f34d62616ce413ull, 0xba121a4650e4ddebull}},
    /* 136 */ { 316, 5, pow5_bits_136, {0xa8c2a44eb4571cdcull, 0x94db483840b717efull}},
    /* 137 */ { 319, 5, pow5_bits_137, {0x746aa07ded582e2cull, 0xee2ba6c0678b597full}},
    /* 138 */ { 321, 6, pow5_bits_138, {0xf6bbb397f1135823ull, 0xbe89523386091465ull}},
    /* 139 */ { 323, 6, pow5_bits_139, {0xf89629465a75e01cull, 0x986ddb5c6b3a76b7ull}},
    /* 140 */ { 326, 6, pow5_bits_140, {0x5a89dba3c3efccfaull, 0xf3e2f893dec3f126ull}},
    /* 141 */ { 328, 6, pow5_bits_141, {0x486e494fcff30a62ull, 0xc31bfa0fe5698db8ull}},
    /* 142 */ { 330, 6, pow5_bits_142, {0x6bea10ca65c084eull, 0x9c1661a651213e2dull}},
    /* 143 */ { 333, 6, pow5_bits_143, {0x3dfdce7aa3c673b0ull, 0xf9bd690a1b68637bull}},
    /* 144 */ { 335, 6, pow5_bits_144, {0xfe64a52ee96b8fc0ull, 0xc7caba6e7c5382c8ull}},
    /* 145 */ { 337, 6, pow5_bits_145, {0xfeb6ea8bedefa633ull, 0x9fd561f1fd0f9bd3ull}},
    /* 146 */ { 340, 6, pow5_bits_146, {0xfdf17746497f7052ull, 0xffbbcfe994e5c61full}},
    /* 147 */ { 342, 6, pow5_bits_147, {0x318df905079926a8ull, 0xcc963fee10b7d1b3ull}},
    /* 148 */ { 344, 6, pow5_bits_148, {0xc13e60d0d2e0ebbaull, 0xa3ab66580d5fdaf5ull}},
    /* 149 */ { 346, 6, pow5_bits_149, {0x9a984d73dbe722fbull, 0x82ef85133de648c4ull}},
    /* 150 */ { 349, 6, pow5_bits_150, {0xf75a15862ca504c5ull, 0xd17f3b51fca3a7a0ull}},
    /* 151 */ { 351, 6, pow5_bits_151, {0x2c48113823b73704ull, 0xa798fc4196e952e7ull}},
    /* 152 */ { 353, 6, pow5_bits_152, {0xbd06742ce95f5f36ull, 0x8613fd0145877585ull}},
    /* 153 */ { 356, 6, pow5_bits_153, {0xc80a537b0efefebdull, 0xd686619ba27255a2ull}},
    /* 154 */ { 358, 6, pow5_bits_154, {0x66ea92f3f326564ull, 0xab9eb47c81f5114full}},
    /* 155 */ { 360, 6, pow5_bits_155, {0x6b8bba8c328eb783ull, 0x894bc396ce5da772ull}},
    /* 156 */ { 363, 6, pow5_bits_156, {0xdf45f746b74abf39ull, 0xdbac6c247d62a583ull}},
    /* 157 */ { 365, 6, pow5_bits_157, {0xe5d1929ef90898faull, 0xafbd2350644eeacfull}},
    /* 158 */ { 367, 6, pow5_bits_158, {0x1e414218c73a13fbull, 0x8c974f7383725573ull}},
    /* 159 */ { 370, 6, pow5_bits_159, {0x306869c13ec3532cull, 0xe0f218b8d25088b8ull}},
    /* 160 */ { 372, 6, pow5_bits_160, {0x59ed216765690f56ull, 0xb3f4e093db73a093ull}},
    /* 161 */ { 374, 6, pow5_bits_161, {0x47f0e785eaba72abull, 0x8ff71a0fe2c2e6dcull}},
    /* 162 */ { 377, 6, pow5_bits_162, {0xcb4a5a3112a5112ull, 0xe65829b3046b0afaull}},
    /* 163 */ { 379, 6, pow5_bits_163, {0x3d5d514f40eea742ull, 0xb84687c269ef3bfbull}},
    /* 164 */ { 381, 6, pow5_bits_164, {0xcab10dd900beec34ull, 0x936b9fcebb25c995ull}},
    /* 165 */ { 384, 6, pow5_bits_165, {0x111b495b3464ad21ull, 0xebdf661791d60f56ull}},
    /* 166 */ { 386, 7, pow5_bits_166, {0x7415d448f6b6f0e7ull, 0xbcb2b812db11a5deull}},
    /* 167 */ { 388, 7, pow5_bits_167, {0x29ab103a5ef8c0b9ull, 0x96f5600f15a7b7e5ull}},
    /* 168 */ { 391, 7, pow5_bits_168, {0xdc44e6c3cb279ac1ull, 0xf18899b1bc3f8ca1ull}},
    /* 169 */ { 393, 7, pow5_bits_169, {0xe36a52363c1faf01ull, 0xc13a148e3032d6e7ull}},
    /* 170 */ { 395, 7, pow5_bits_170, {0x82bb74f8301958ceull, 0x9a94dd3e8cf578b9ull}},
    /* 171 */ { 398, 7, pow5_bits_171, {0xd12bee59e68ef47cull, 0xf7549530e188c128ull}},
    /* 172 */ { 400, 7, pow5_bits_172, {0x40eff1e1853f29fdull, 0xc5dd44271ad3cdbaull}},
    /* 173 */ { 402, 7, pow5_bits_173, {0x9a598e4e043287feull, 0x9e4a9cec15763e2eull}},
    /* 174 */ { 405, 7, pow5_bits_174, {0x908f4a166d1da663ull, 0xfd442e4688bd304aull}},
    /* 175 */ { 407, 7, pow5_bits_175, {0xa6d90811f0e4851cull, 0xca9cf1d206fdc03bull}},
    /* 176 */ { 409, 7, pow5_bits_176, {0xb8ada00e5a506a7cull, 0xa21727db38cb002full}},
    /* 177 */ { 411, 7, pow5_bits_177, {0xc6f14cd848405530ull, 0x81ac1fe293d599bfull}},
    /* 178 */ { 414, 7, pow5_bits_178, {0x7182148d4066eeb4ull, 0xcf79cc9db955c2ccull}},
    /* 179 */ { 416, 7, pow5_bits_179, {0xf468107100525890ull, 0xa5fb0a17c777cf09ull}},
    /* 180 */ { 418, 7, pow5_bits_180, {0x29ecd9f40041e073ull, 0x84c8d4dfd2c63f3bull}},
    /* 181 */ { 421, 7, pow5_bits_181, {0x7647c3200069671full, 0xd47487cc8470652bull}},
    /* 182 */ { 423, 7, pow5_bits_182, {0x5e9fcf4ccd211f4cull, 0xa9f6d30a038d1dbcull}},
    /* 183 */ { 425, 7, pow5_bits_183, {0xe54ca5d70a80e5d6ull, 0x87f8a8d4cfa417c9ull}},
    /* 184 */ { 428, 7, pow5_bits_184, {0x3badd624dd9b0957ull, 0xd98ddaee19068c76ull}},
    /* 185 */ { 430, 7, pow5_bits_185, {0x9624ab50b148d445ull, 0xae0b158b4738705eull}},
    /* 186 */ { 432, 7, pow5_bits_186, {0xde83bc408dd3dd04ull, 0x8b3c113c38f9f37eull}},
    /* 187 */ { 435, 7, pow5_bits_187, {0x6405fa00e2ec94d4ull, 0xdec681f9f4c31f31ull}},
    /* 188 */ { 437, 7, pow5_bits_188, {0xe99e619a4f23aa43ull, 0xb23867fb2a35b28dull}},
    /* 189 */ { 439, 7, pow5_bits_189, {0x547eb47b7282ee9cull, 0x8e938662882af53eull}},
    /* 190 */ { 442, 7, pow5_bits_190, {0x20caba5f1d9e4a93ull, 0xe41f3d6a7377eecaull}},
    /* 191 */ { 444, 7, pow5_bits_191, {0x1a3bc84c17b1d542ull, 0xb67f6455292cbf08ull}},
    /* 192 */ { 446, 7, pow5_bits_192, {0x7b6306a34627ddcfull, 0x91ff83775423cc06ull}},
    /* 193 */ { 449, 8, pow5_bits_193, {0x2bd1a438703fc94bull, 0xe998d258869facd7ull}},
    /* 194 */ { 451, 8, pow5_bits_194, {0x8974836059cca109ull, 0xbae0a846d2195712ull}},
    /* 195 */ { 453, 8, pow5_bits_195, {0xd45d35e6ae3d4da0ull, 0x9580869f0e7aac0eull}},
    /* 196 */ { 456, 8, pow5_bits_196, {0x86fb897116c87c34ull, 0xef340a98172aace4ull}},
    /* 197 */ { 458, 8, pow5_bits_197, {0xd262d45a78a0635dull, 0xbf5cd54678eef0b6ull}},
    /* 198 */ { 460, 8, pow5_bits_198, {0x751bdd152d4d1c4aull, 0x991711052d8bf3c5ull}},
    /* 199 */ { 463, 8, pow5_bits_199, {0xee92fb5515482d44ull, 0xf4f1b4d515acb93bull}},
    /* 200 */ { 465, 8, pow5_bits_200, {0xbedbfc4411068a9cull, 0xc3f490aa77bd60fcull}},
    /* 201 */ { 467, 8, pow5_bits_201, {0xcbe3303674053bb0ull, 0x9cc3a6eec6311a63ull}},
    /* 202 */ { 470, 8, pow5_bits_202, {0x796b805720085f81ull, 0xfad2a4b13d1b5d6cull}},
    /* 203 */ { 472, 8, pow5_bits_203, {0x6122cd128006b2cdull, 0xc8a883c0fdaf7df0ull}},
    /* 204 */ { 474, 8, pow5_bits_204, {0x80e8a40eccd228a4ull, 0xa086cfcd97bf97f3ull}},
    /* 205 */ { 476, 8, pow5_bits_205, {0xba1cd8a3db53b6ull, 0x806bd9714632dff6ull}},
    /* 206 */ { 479, 8, pow5_bits_206, {0x67902e276c921f8bull, 0xcd795be870516656ull}},
    /* 207 */ { 481, 8, pow5_bits_207, {0x52d9be85f074e608ull, 0xa46116538d0deb78ull}},
    /* 208 */ { 483, 8, pow5_bits_208, {0x4247cb9e59f71e6dull, 0x8380dea93da4bc60ull}},
    /* 209 */ { 486, 8, pow5_bits_209, {0xd072df63c324fd7bull, 0xd267caa862a12d66ull}},
    /* 210 */ { 488, 8, pow5_bits_210, {0xd9f57f830283fdfcull, 0xa8530886b54dbdebull}},
    /* 211 */ { 490, 8, pow5_bits_211, {0xae5dff9c02033197ull, 0x86a8d39ef77164bcull}},
    /* 212 */ { 493, 8, pow5_bits_212, {0x7d633293366b828bull, 0xd77485cb25823ac7ull}},
    /* 213 */ { 495, 8, pow5_bits_213, {0x311c2875c522ced5ull, 0xac5d37d5b79b6239ull}},
    /* 214 */ { 497, 8, pow5_bits_214, {0xf41686c49db57244ull, 0x89e42caaf9491b60ull}},
    /* 215 */ { 500, 8, pow5_bits_215, {0xecf0d7a0fc5583a0ull, 0xdca04777f541c567ull}},
    /* 216 */ { 502, 8, pow5_bits_216, {0xbd8d794d96aacfb3ull, 0xb080392cc4349decull}},
    /* 217 */ { 504, 8, pow5_bits_217, {0x64712dd7abbbd95cull, 0x8d3360f09cf6e4bdull}},
    /* 218 */ { 507, 8, pow5_bits_218, {0xd3e8495912c62894ull, 0xe1ebce4dc7f16dfbull}},
    /* 219 */ { 509, 8, pow5_bits_219, {0xfed077a756b53a9ull, 0xb4bca50b065abe63ull}},
    /* 220 */ { 511, 8, pow5_bits_220, {0x3ff0d2c85def7621ull, 0x9096ea6f3848984full}},
    /* 221 */ { 514, 9, pow5_bits_221, {0x331aeada2fe589cfull, 0xe757dd7ec07426e5ull}},
    /* 222 */ { 516, 9, pow5_bits_222, {0x28e2557b59846e3full, 0xb913179899f68584ull}},
    /* 223 */ { 518, 9, pow5_bits_223, {0x871b7795e136be99ull, 0x940f4613ae5ed136ull}},
    /* 224 */ { 521, 9, pow5_bits_224, {0xa4f8bf5635246428ull, 0xece53cec4a314ebdull}},
    /* 225 */ { 523, 9, pow5_bits_225, {0x50c6ff782a838353ull, 0xbd8430bd08277231ull}},
    /* 226 */ { 525, 9, pow5_bits_226, {0xa705992ceecf9c42ull, 0x979cf3ca6cec5b5aull}},
    /* 227 */ { 528, 9, pow5_bits_227, {0x3e6f5b7b17b2939dull, 0xf294b943e17a2bc4ull}},
    /* 228 */ { 530, 9, pow5_bits_228, {0x985915fc12f542e4ull, 0xc21094364dfb5636ull}},
    /* 229 */ { 532, 9, pow5_bits_229, {0x79e0de63425dcf1dull, 0x9b407691d7fc44f8ull}},
    /* 230 */ { 535, 9, pow5_bits_230, {0xc30163d203c94b62ull, 0xf867241c8cc6d4c0ull}},
    /* 231 */ { 537, 9, pow5_bits_231, {0x359ab6419ca1091bull, 0xc6b8e9b0709f109aull}},
    /* 232 */ { 539, 9, pow5_bits_232, {0xc47bc5014a1a6dafull, 0x9efa548d26e5a6e1ull}},
    /* 233 */ { 542, 9, pow5_bits_233, {0xd3f93b35435d7c4cull, 0xfe5d54150b090b02ull}},
    /* 234 */ { 544, 9, pow5_bits_234, {0xa9942f5dcf7dfd09ull, 0xcb7ddcdda26da268ull}},
    /* 235 */ { 546, 9, pow5_bits_235, {0x54768c4b0c64ca6eull, 0xa2cb1717b52481edull}},
    /* 236 */ { 548, 9, pow5_bits_236, {0x76c53d08d6b70858ull, 0x823c12795db6ce57ull}},
    /* 237 */ { 551, 9, pow5_bits_237, {0xf13b94daf124da26ull, 0xd0601d8efc57b08bull}},
    /* 238 */ { 553, 9, pow5_bits_238, {0xf42faa48c0ea481eull, 0xa6b34ad8c9dfc06full}},
    /* 239 */ { 555, 9, pow5_bits_239, {0x5cf2eea09a55067full, 0x855c3be0a17fcd26ull}},
    /* 240 */ { 558, 9, pow5_bits_240, {0xfb1e4a9a90880a64ull, 0xd5605fcdcf32e1d6ull}},
    /* 241 */ { 560, 9, pow5_bits_241, {0xc8e5087ba6d33b83ull, 0xaab37fd7d8f58178ull}},
    /* 242 */ { 562, 9, pow5_bits_242, {0x6d8406c952429603ull, 0x888f99797a5e012dull}},
    /* 243 */ { 565, 9, pow5_bits_243, {0xaf39a475506a899eull, 0xda7f5bf590966848ull}},
    /* 244 */ { 567, 9, pow5_bits_244, {0x58fae9f773886e18ull, 0xaecc49914078536dull}},
    /* 245 */ { 569, 9, pow5_bits_245, {0xe0c8bb2c5c6d24e0ull, 0x8bd6a141006042bdull}},
    /* 246 */ { 572, 9, pow5_bits_246, {0x67a791e093e1d49aull, 0xdfbdcece67006ac9ull}},
    /* 247 */ { 574, 9, pow5_bits_247, {0x861fa7e6dcb4aa15ull, 0xb2fe3f0b8599ef07ull}},
    /* 248 */ { 576, 9, pow5_bits_248, {0xd1b2ecb8b0908810ull, 0x8f31cc0937ae58d2ull}},
    /* 249 */ { 579, 10, pow5_bits_249, {0x82b7e12780e7401aull, 0xe51c79a85916f484ull}},
    /* 250 */ { 581, 10, pow5_bits_250, {0xcef980ec671f667bull, 0xb749faed14125d36ull}},
    /* 251 */ { 583, 10, pow5_bits_251, {0xbfacd89ec191ec9ull, 0x92a1958a7675175full}},
    /* 252 */ { 586, 10, pow5_bits_252, {0x465e15a979c1cadcull, 0xea9c227723ee8bcbull}},
    /* 253 */ { 588, 10, pow5_bits_253, {0x9eb1aaedfb016f16ull, 0xbbb01b9283253ca2ull}},
    /* 254 */ { 590, 10, pow5_bits_254, {0x4bc1558b2f3458deull, 0x96267c7535b763b5ull}},
    /* 255 */ { 593, 10, pow5_bits_255, {0x793555ab7eba27caull, 0xf03d93eebc589f88ull}},
    /* 256 */ { 595, 10, pow5_bits_256, {0xfa911155fefb5308ull, 0xc0314325637a1939ull}},
    /* 257 */ { 597, 10, pow5_bits_257, {0x2eda7444cbfc426dull, 0x99c102844f94e0fbull}},
    /* 258 */ { 600, 10, pow5_bits_258, {0x7e2a53a146606a48ull, 0xf6019da07f549b2bull}},
    /* 259 */ { 602, 10, pow5_bits_259, {0xcb550fb4384d21d3ull, 0xc4ce17b399107c22ull}},
    /* 260 */ { 604, 10, pow5_bits_260, {0x6f773fc3603db4a9ull, 0x9d71ac8fada6c9b5ull}},
    /* 261 */ { 607, 10, pow5_bits_261, {0x4bf1ff9f0062baa8ull, 0xfbe9141915d7a922ull}},
    /* 262 */ { 609, 10, pow5_bits_262, {0xa327ffb266b56220ull, 0xc987434744ac874eull}},
    /* 263 */ { 611, 10, pow5_bits_263, {0x1c1fffc1ebc44e80ull, 0xa139029f6a239f72ull}},
    /* 264 */ { 613, 10, pow5_bits_264, {0x7ce66634bc9d0b99ull, 0x80fa687f881c7f8eull}},
    /* 265 */ { 616, 10, pow5_bits_265, {0xfb0a3d212dc8128full, 0xce5d73ff402d98e3ull}},
    /* 266 */ { 618, 10, pow5_bits_266, {0x626e974dbe39a872ull, 0xa5178fff668ae0b6ull}},
    /* 267 */ { 620, 10, pow5_bits_267, {0xe858790afe9486c2ull, 0x8412d9991ed58091ull}},
    /* 268 */ { 623, 10, pow5_bits_268, {0xd5a5b44ca873e03ull, 0xd3515c2831559a83ull}},
    /* 269 */ { 625, 10, pow5_bits_269, {0x711515d0a205cb36ull, 0xa90de3535aaae202ull}},
    /* 270 */ { 627, 10, pow5_bits_270, {0x5a7744a6e804a291ull, 0x873e4f75e2224e68ull}},
    /* 271 */ { 630, 10, pow5_bits_271, {0x90bed43e40076a82ull, 0xd863b256369d4a40ull}},
    /* 272 */ { 632, 10, pow5_bits_272, {0xda3243650005eecfull, 0xad1c8eab5ee43b66ull}},
    /* 273 */ { 634, 10, pow5_bits_273, {0x482835ea666b2572ull, 0x8a7d3eef7f1cfc52ull}},
    /* 274 */ { 637, 10, pow5_bits_274, {0x40405643d711d583ull, 0xdd95317f31c7fa1dull}},
    /* 275 */ { 639, 10, pow5_bits_275, {0x99cd11cfdf41779cull, 0xb1442798f49ffb4aull}},
    /* 276 */ { 641, 11, pow5_bits_276, {0xae3da7d97f6792e3ull, 0x8dd01fad907ffc3bull}},
    /* 277 */ { 644, 11, pow5_bits_277, {0x16c90c8f323f516cull, 0xe2e69915b3fff9f9ull}},
    /* 278 */ { 646, 11, pow5_bits_278, {0xabd40a0c2832a78aull, 0xb58547448ffffb2dull}},
    /* 279 */ { 648, 11, pow5_bits_279, {0x23100809b9c21fa1ull, 0x91376c36d99995beull}},
    /* 280 */ { 651, 11, pow5_bits_280, {0xd1b3400f8f9cff68ull, 0xe858ad248f5c22c9ull}},
    /* 281 */ { 653, 11, pow5_bits_281, {0xdaf5ccd93fb0cc53ull, 0xb9e08a83a5e34f07ull}},
    /* 282 */ { 655, 11, pow5_bits_282, {0x7bf7d71432f3d6a9ull, 0x94b3a202eb1c3f39ull}},
    /* 283 */ { 658, 11, pow5_bits_283, {0x2cbfbe86b7ec8aa8ull, 0xedec366b11c6cb8full}},
    /* 284 */ { 660, 11, pow5_bits_284, {0x23cc986bc656d553ull, 0xbe5691ef416bd60cull}},
    /* 285 */ { 662, 11, pow5_bits_285, {0x830a13896b78aaa9ull, 0x9845418c345644d6ull}},
    /* 286 */ { 665, 11, pow5_bits_286, {0x6b43527578c1110full, 0xf3a20279ed56d48aull}},
    /* 287 */ { 667, 11, pow5_bits_287, {0x229c41f793cda73full, 0xc2e801fb244576d5ull}},
    /* 288 */ { 669, 11, pow5_bits_288, {0x4ee367f9430aec32ull, 0x9becce62836ac577ull}},
    /* 289 */ { 672, 11, pow5_bits_289, {0x4b0573286b44ad1dull, 0xf97ae3d0d2446f25ull}},
    /* 290 */ { 674, 11, pow5_bits_290, {0xd59df5b9ef6a2417ull, 0xc795830d75038c1dull}},
    /* 291 */ { 676, 11, pow5_bits_291, {0x77b191618c54e9acull, 0x9faacf3df73609b1ull}},
    /* 292 */ { 679, 11, pow5_bits_292, {0x25e8e89c13bb0f7aull, 0xff77b1fcbebcdc4full}},
    /* 293 */ { 681, 11, pow5_bits_293, {0x1e53ed49a96272c8ull, 0xcc5fc196fefd7d0cull}},
    /* 294 */ { 683, 11, pow5_bits_294, {0xe50ff107bab528a0ull, 0xa37fce126597973cull}},
    /* 295 */ { 685, 11, pow5_bits_295, {0x50d98d9fc890ed4dull, 0x82cca4db847945caull}},
    /* 296 */ { 688, 11, pow5_bits_296, {0x1af5af660db4aee1ull, 0xd1476e2c07286faaull}},
    /* 297 */ { 690, 11, pow5_bits_297, {0xaf2af2b80af6f24eull, 0xa76c582338ed2621ull}},
    /* 298 */ { 692, 11, pow5_bits_298, {0x25bbf56008c58ea5ull, 0x85f0468293f0eb4eull}},
    /* 299 */ { 695, 11, pow5_bits_299, {0x92cbbccdad5b108ull, 0xd64d3d9db981787dull}},
    /* 300 */ { 697, 11, pow5_bits_300, {0x6dbd630a48aaf406ull, 0xab70fe17c79ac6caull}},
    /* 301 */ { 699, 11, pow5_bits_301, {0xbe311c083a225cd2ull, 0x892731ac9faf056eull}},
    /* 302 */ { 702, 11, pow5_bits_302, {0xc9e82cd9f69d6150ull, 0xdb71e91432b1a24aull}},
    /* 303 */ { 704, 11, pow5_bits_303, {0x7ecf0ae5ee44dd9ull, 0xaf8e5410288e1b6full}},
    /* 304 */ { 706, 12, pow5_bits_304, {0x9ff0c08b7f1d0b14ull, 0x8c71dcd9ba0b4925ull}},
    /* 305 */ { 709, 12, pow5_bits_305, {0x331acdabfe94de87ull, 0xe0b62e2929aba83cull}},
    /* 306 */ { 711, 12, pow5_bits_306, {0x8f48a4899877186cull, 0xb3c4f1ba87bc8696ull}},
    /* 307 */ { 713, 12, pow5_bits_307, {0xa5d3b6d479f8e056ull, 0x8fd0c16206306babull}},
    /* 308 */ { 716, 12, pow5_bits_308, {0x6fb92487298e33bdull, 0xe61acf033d1a45dfull}},
    /* 309 */ { 718, 12, pow5_bits_309, {0x5960ea05bad82964ull, 0xb8157268fdae9e4cull}},
    /* 310 */ { 720, 12, pow5_bits_310, {0x7ab3ee6afbe0211dull, 0x93445b8731587ea3ull}},
    /* 311 */ { 723, 12, pow5_bits_311, {0xf7864a44c633682eull, 0xeba09271e88d976bull}},
    /* 312 */ { 725, 12, pow5_bits_312, {0xc605083704f5ecf2ull, 0xbc807527ed3e12bcull}},
    /* 313 */ { 727, 12, pow5_bits_313, {0x380406926a5e5728ull, 0x96cd2a865764dbcaull}},
    /* 314 */ { 730, 12, pow5_bits_314, {0xc00670ea43ca250dull, 0xf148440a256e2c76ull}},
    /* 315 */ { 732, 12, pow5_bits_315, {0x999ec0bb696e840aull, 0xc1069cd4eabe89f8ull}},
    /* 316 */ { 734, 12, pow5_bits_316, {0x47b233c92125366eull, 0x9a6bb0aa55653b2dull}},
    /* 317 */ { 737, 12, pow5_bits_317, {0xa5e9ec7501d523e4ull, 0xf712b443bbd52b7bull}},
    /* 318 */ { 739, 12, pow5_bits_318, {0xeb2189f734aa831dull, 0xc5a890362fddbc62ull}},
    /* 319 */ { 741, 12, pow5_bits_319, {0x55b46e5f5d5535b0ull, 0x9e20735e8cb16382ull}},
    /* 320 */ { 744, 12, pow5_bits_320, {0x8920b098955522b4ull, 0xfd00b897478238d0ull}},
    /* 321 */ { 746, 12, pow5_bits_321, {0xd41a26e077774ef6ull, 0xca66fa129f9b60a6ull}},
    /* 322 */ { 748, 12, pow5_bits_322, {0x1014ebe6c5f90bf8ull, 0xa1ebfb4219491a1full}},
    /* 323 */ { 750, 12, pow5_bits_323, {0x7343efebd1940993ull, 0x818995ce7aa0e1b2ull}},
    /* 324 */ { 753, 12, pow5_bits_324, {0x52064cac828675b9ull, 0xcf42894a5dce35eaull}},
    /* 325 */ { 755, 12, pow5_bits_325, {0x419ea3bd35385e2dull, 0xa5ced43b7e3e9188ull}},
    /* 326 */ { 757, 12, pow5_bits_326, {0x14bb630f7604b57ull, 0x84a57695fe98746dull}},
    /* 327 */ { 760, 12, pow5_bits_327, {0x212bd1b2566def2ull, 0xd43bf0effdc0ba48ull}},
    /* 328 */ { 762, 12, pow5_bits_328, {0x680efdaf511f18c2ull, 0xa9c98d8ccb009506ull}},
    /* 329 */ { 764, 12, pow5_bits_329, {0x8672648c40e5ad68ull, 0x87d4713d6f33aa6bull}},
};
