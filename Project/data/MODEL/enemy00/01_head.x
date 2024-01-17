xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 86;
 1.63515;3.03265;-3.47274;,
 1.15622;4.33656;-3.47274;,
 -1.63515;3.03265;-3.47274;,
 0.00000;4.87665;-3.47274;,
 -1.15622;4.33656;-3.47274;,
 0.00000;3.03265;-6.74306;,
 -1.46418;-0.36023;1.50916;,
 0.00000;-0.36023;2.11564;,
 0.00000;0.81269;3.87106;,
 -2.70544;0.81269;2.75043;,
 1.46418;-0.36023;1.50916;,
 2.70544;0.81269;2.75043;,
 2.07066;-0.36023;0.04499;,
 3.82607;0.81269;0.04499;,
 2.07066;-0.36023;0.04499;,
 1.46418;-0.36023;-1.41918;,
 2.70544;0.81269;-2.66045;,
 3.82607;0.81269;0.04499;,
 0.00000;-0.36023;-2.02566;,
 0.00000;0.81269;-3.78108;,
 -1.46418;-0.36023;-1.41918;,
 -2.70544;0.81269;-2.66045;,
 -2.07066;-0.36023;0.04499;,
 -3.82607;0.81269;0.04499;,
 -2.07066;-0.36023;0.04499;,
 -3.82607;0.81269;0.04499;,
 0.00000;2.56811;5.04399;,
 -3.53483;2.56811;3.57982;,
 3.53483;2.56811;3.57982;,
 4.99900;2.56811;0.04499;,
 3.53483;2.56811;-3.48984;,
 4.99900;2.56811;0.04499;,
 0.00000;2.56811;-4.95401;,
 -3.53483;2.56811;-3.48984;,
 -4.99900;2.56811;0.04499;,
 -4.99900;2.56811;0.04499;,
 0.00000;4.63876;5.45587;,
 -3.82607;4.63876;3.87106;,
 3.82607;4.63876;3.87106;,
 5.41088;4.63876;0.04499;,
 3.82607;4.63876;-3.78108;,
 5.41088;4.63876;0.04499;,
 0.00000;4.63876;-5.36589;,
 -3.82607;4.63876;-3.78108;,
 -5.41088;4.63876;0.04499;,
 -5.41088;4.63876;0.04499;,
 0.00000;6.70942;5.04399;,
 -3.53483;6.70942;3.57982;,
 3.53483;6.70942;3.57982;,
 4.99900;6.70942;0.04499;,
 3.53483;6.70942;-3.48984;,
 4.99900;6.70942;0.04499;,
 0.00000;6.70942;-4.95401;,
 -3.53483;6.70942;-3.48984;,
 -4.99900;6.70942;0.04499;,
 -4.99900;6.70942;0.04499;,
 0.00000;8.46483;3.87106;,
 -2.70544;8.46483;2.75043;,
 2.70544;8.46483;2.75043;,
 3.82607;8.46483;0.04499;,
 2.70544;8.46483;-2.66045;,
 3.82607;8.46483;0.04499;,
 0.00000;8.46483;-3.78108;,
 -2.70544;8.46483;-2.66045;,
 -3.82607;8.46483;0.04499;,
 -3.82607;8.46483;0.04499;,
 0.00000;9.63776;2.11564;,
 -1.46418;9.63776;1.50916;,
 1.46418;9.63776;1.50916;,
 2.07066;9.63776;0.04499;,
 1.46418;9.63776;-1.41918;,
 2.07066;9.63776;0.04499;,
 0.00000;9.63776;-2.02566;,
 -1.46418;9.63776;-1.41918;,
 -2.07066;9.63776;0.04499;,
 -2.07066;9.63776;0.04499;,
 0.00000;-0.77211;0.04499;,
 0.00000;-0.77211;0.04499;,
 0.00000;10.04964;0.04499;,
 0.00000;10.04964;0.04499;,
 1.63515;3.25236;-3.50800;,
 -1.63515;3.25236;-3.50800;,
 1.15622;1.97657;-3.23871;,
 0.00000;1.44810;-3.12716;,
 -1.15622;1.97657;-3.23871;,
 0.00000;2.57698;-6.70779;;
 
 80;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 3;4,3,5;,
 3;3,1,5;,
 3;1,0,5;,
 3;0,2,5;,
 3;2,4,5;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;10,12,13,11;,
 4;14,15,16,17;,
 4;15,18,19,16;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;24,6,9,25;,
 4;9,8,26,27;,
 4;8,11,28,26;,
 4;11,13,29,28;,
 4;17,16,30,31;,
 4;16,19,32,30;,
 4;19,21,33,32;,
 4;21,23,34,33;,
 4;25,9,27,35;,
 4;27,26,36,37;,
 4;26,28,38,36;,
 4;28,29,39,38;,
 4;31,30,40,41;,
 4;30,32,42,40;,
 4;32,33,43,42;,
 4;33,34,44,43;,
 4;35,27,37,45;,
 4;37,36,46,47;,
 4;36,38,48,46;,
 4;38,39,49,48;,
 4;41,40,50,51;,
 4;40,42,52,50;,
 4;42,43,53,52;,
 4;43,44,54,53;,
 4;45,37,47,55;,
 4;47,46,56,57;,
 4;46,48,58,56;,
 4;48,49,59,58;,
 4;51,50,60,61;,
 4;50,52,62,60;,
 4;52,53,63,62;,
 4;53,54,64,63;,
 4;55,47,57,65;,
 4;57,56,66,67;,
 4;56,58,68,66;,
 4;58,59,69,68;,
 4;61,60,70,71;,
 4;60,62,72,70;,
 4;62,63,73,72;,
 4;63,64,74,73;,
 4;65,57,67,75;,
 3;7,6,76;,
 3;10,7,76;,
 3;12,10,76;,
 3;15,14,77;,
 3;18,15,77;,
 3;20,18,77;,
 3;22,20,77;,
 3;6,24,76;,
 3;67,66,78;,
 3;66,68,78;,
 3;68,69,78;,
 3;71,70,79;,
 3;70,72,79;,
 3;72,73,79;,
 3;73,74,79;,
 3;75,67,78;,
 3;80,81,82;,
 3;82,81,83;,
 3;81,84,83;,
 3;82,83,85;,
 3;83,84,85;,
 3;84,81,85;,
 3;81,80,85;,
 3;80,82,85;;
 
 MeshMaterialList {
  1;
  80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy01_00.png";
   }
  }
 }
 MeshNormals {
  77;
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.871069;-0.491161;,
  -0.269132;-0.924736;0.269132;,
  0.000000;-0.924735;0.380610;,
  0.269132;-0.924736;0.269132;,
  0.380611;-0.924735;-0.000000;,
  0.269132;-0.924735;-0.269133;,
  0.000000;-0.924735;-0.380611;,
  -0.269132;-0.924735;-0.269132;,
  -0.380611;-0.924735;-0.000000;,
  -0.498494;-0.709231;0.498494;,
  0.000000;-0.709230;0.704977;,
  0.498494;-0.709231;0.498494;,
  0.704977;-0.709230;-0.000000;,
  0.498494;-0.709231;-0.498494;,
  0.000000;-0.709231;-0.704976;,
  -0.498494;-0.709231;-0.498494;,
  -0.704977;-0.709230;-0.000000;,
  -0.652733;-0.384551;0.652733;,
  0.000000;-0.384550;0.923104;,
  0.652733;-0.384551;0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;-0.652733;,
  0.000000;-0.384551;-0.923104;,
  -0.652733;-0.384551;-0.652733;,
  -0.923104;-0.384551;-0.000000;,
  -0.707106;-0.000000;0.707107;,
  0.000000;-0.000000;1.000000;,
  0.707106;-0.000000;0.707107;,
  1.000000;-0.000000;-0.000000;,
  0.707106;-0.000000;-0.707107;,
  0.000000;-0.000000;-1.000000;,
  -0.707106;-0.000000;-0.707107;,
  -1.000000;-0.000000;-0.000000;,
  -0.652733;0.384551;0.652733;,
  0.000000;0.384550;0.923104;,
  0.652733;0.384551;0.652733;,
  0.923104;0.384551;-0.000000;,
  0.652733;0.384550;-0.652733;,
  0.000000;0.384550;-0.923104;,
  -0.652733;0.384550;-0.652733;,
  -0.923104;0.384551;-0.000000;,
  -0.498494;0.709231;0.498494;,
  0.000000;0.709231;0.704977;,
  0.498494;0.709231;0.498494;,
  0.704976;0.709231;-0.000000;,
  0.498494;0.709231;-0.498494;,
  0.000000;0.709231;-0.704976;,
  -0.498494;0.709231;-0.498494;,
  -0.704976;0.709231;-0.000000;,
  -0.269132;0.924736;0.269132;,
  0.000000;0.924736;0.380610;,
  0.269132;0.924736;0.269132;,
  0.380611;0.924735;-0.000000;,
  0.269132;0.924735;-0.269132;,
  0.000000;0.924735;-0.380610;,
  -0.269132;0.924735;-0.269132;,
  -0.380611;0.924735;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000001;0.206529;0.978441;,
  -0.000002;0.206528;0.978441;,
  -0.000006;0.206524;0.978442;,
  -0.000001;0.206527;0.978441;,
  0.000000;0.206526;0.978441;,
  0.000000;-0.953724;-0.300684;,
  -0.652802;0.595493;-0.468228;,
  0.652802;0.595493;-0.468228;,
  0.849747;0.312112;-0.424871;,
  0.000000;-1.000000;0.000000;,
  -0.849747;0.312112;-0.424871;,
  0.652803;-0.679352;-0.335155;,
  -0.652803;-0.679352;-0.335155;,
  -0.849744;-0.393132;-0.351257;,
  0.000000;0.978442;-0.206521;,
  0.849744;-0.393132;-0.351257;;
  80;
  3;1,1,1;,
  3;1,1,1;,
  3;1,0,1;,
  3;67,2,2;,
  3;2,68,2;,
  3;68,69,69;,
  3;70,70,70;,
  3;71,67,71;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,3,11,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,11,19,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,19,27,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,27,35,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,35,43,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,43,51,58;,
  3;4,3,59;,
  3;5,4,59;,
  3;6,5,59;,
  3;7,6,59;,
  3;8,7,59;,
  3;9,8,59;,
  3;10,9,59;,
  3;3,10,59;,
  3;51,52,60;,
  3;52,53,60;,
  3;53,54,60;,
  3;54,55,60;,
  3;55,56,60;,
  3;56,57,60;,
  3;57,58,60;,
  3;58,51,60;,
  3;65,64,61;,
  3;61,64,62;,
  3;64,63,62;,
  3;72,66,66;,
  3;66,73,66;,
  3;73,74,74;,
  3;75,75,75;,
  3;76,72,76;;
 }
 MeshTextureCoords {
  86;
  0.639360;0.407110;,
  0.653190;0.407110;,
  0.733760;0.407110;,
  0.686560;0.407110;,
  0.719930;0.407110;,
  0.686560;0.493520;,
  0.912230;0.605750;,
  0.882500;0.605750;,
  0.882500;0.581940;,
  0.937430;0.581940;,
  0.852770;0.605750;,
  0.827560;0.581940;,
  0.840450;0.605750;,
  0.804810;0.581940;,
  0.745850;0.355150;,
  0.765620;0.355150;,
  0.725160;0.316240;,
  0.688640;0.316240;,
  0.813340;0.355150;,
  0.813340;0.316240;,
  0.861060;0.355150;,
  0.901520;0.316240;,
  0.880830;0.355150;,
  0.938050;0.316240;,
  0.924540;0.605750;,
  0.960190;0.581940;,
  0.882500;0.546290;,
  0.954270;0.546290;,
  0.810720;0.546290;,
  0.780990;0.546290;,
  0.698130;0.258000;,
  0.650410;0.258000;,
  0.813340;0.258000;,
  0.928550;0.258000;,
  0.976280;0.258000;,
  0.984000;0.546290;,
  0.882500;0.504250;,
  0.960190;0.504250;,
  0.804810;0.504250;,
  0.772630;0.504250;,
  0.688640;0.189310;,
  0.636980;0.189310;,
  0.813340;0.189310;,
  0.938050;0.189310;,
  0.989700;0.189310;,
  0.992370;0.504250;,
  0.882500;0.462200;,
  0.954270;0.462200;,
  0.810720;0.462200;,
  0.780990;0.462200;,
  0.698130;0.120620;,
  0.650410;0.120620;,
  0.813340;0.120620;,
  0.928550;0.120620;,
  0.976280;0.120620;,
  0.984000;0.462200;,
  0.882500;0.426560;,
  0.937430;0.426560;,
  0.827560;0.426560;,
  0.804810;0.426560;,
  0.725160;0.062390;,
  0.688640;0.062390;,
  0.813340;0.062390;,
  0.901520;0.062390;,
  0.938050;0.062390;,
  0.960190;0.426560;,
  0.882500;0.402740;,
  0.912230;0.402740;,
  0.852770;0.402740;,
  0.840450;0.402740;,
  0.765620;0.023480;,
  0.745850;0.023480;,
  0.813340;0.023480;,
  0.861060;0.023480;,
  0.880830;0.023480;,
  0.924540;0.402740;,
  0.882500;0.614120;,
  0.813340;0.368810;,
  0.882500;0.394380;,
  0.813340;0.009820;,
  0.639360;0.408050;,
  0.733760;0.408050;,
  0.653190;0.401740;,
  0.686560;0.399120;,
  0.719930;0.401740;,
  0.686560;0.492590;;
 }
}
