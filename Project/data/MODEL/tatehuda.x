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
 75;
 94.34282;186.73991;-6.04111;,
 94.34282;186.73991;16.71999;,
 94.34282;176.64473;16.71999;,
 94.34282;176.64473;-6.04111;,
 -95.22571;186.73991;16.71999;,
 -95.22571;186.73991;-6.04111;,
 -95.22571;176.64473;-6.04111;,
 -95.22571;176.64473;16.71999;,
 94.34282;186.73991;-6.04111;,
 94.34282;176.64473;-6.04111;,
 -0.44160;213.05464;-6.04111;,
 -0.44160;223.14995;-6.04111;,
 -95.22571;176.64473;-6.04111;,
 -95.22571;186.73991;-6.04111;,
 -95.22571;186.73991;-6.04111;,
 -0.44160;223.14995;16.71999;,
 -0.44160;223.14995;-6.04111;,
 94.34282;186.73991;-6.04111;,
 -0.44160;213.05464;16.71999;,
 -0.44160;213.05464;-6.04111;,
 94.34282;176.64473;-6.04111;,
 -95.22571;176.64473;-6.04111;,
 94.34282;186.73991;16.71999;,
 94.34282;176.64473;16.71999;,
 -95.22571;186.73991;16.71999;,
 -95.22571;176.64473;16.71999;,
 68.44090;186.34704;-0.49372;,
 68.44090;186.34704;11.17261;,
 68.44090;113.90794;11.17261;,
 68.44090;113.90794;-0.49372;,
 -69.32377;186.34704;11.17261;,
 -69.32377;186.34704;-0.49372;,
 -69.32377;113.90794;-0.49372;,
 -69.32377;113.90794;11.17261;,
 68.44090;186.34704;-0.49372;,
 68.44090;113.90794;-0.49372;,
 -0.44160;115.06699;-0.49372;,
 -0.44160;213.02134;-0.49372;,
 -69.32377;113.90794;-0.49372;,
 -69.32377;186.34704;-0.49372;,
 -69.32377;186.34704;-0.49372;,
 -0.44160;213.02134;11.17261;,
 -0.44160;213.02134;-0.49372;,
 68.44090;186.34704;-0.49372;,
 -0.44160;115.06699;11.17261;,
 -0.44160;115.06699;-0.49372;,
 68.44090;113.90794;-0.49372;,
 -69.32377;113.90794;-0.49372;,
 68.44090;186.34704;11.17261;,
 68.44090;113.90794;11.17261;,
 -69.32377;186.34704;11.17261;,
 -69.32377;113.90794;11.17261;,
 -0.44160;213.02134;11.17261;,
 -3.98655;171.79657;11.37518;,
 -0.44160;115.06699;11.17261;,
 8.38300;115.65922;1.48353;,
 8.38300;1.27930;1.48353;,
 -9.26604;1.27930;1.48353;,
 -9.26604;115.65922;1.48353;,
 8.38300;1.27930;1.48353;,
 8.38300;1.27930;9.19536;,
 -9.26604;1.27930;9.19536;,
 -9.26604;1.27930;1.48353;,
 8.38300;1.27930;9.19536;,
 8.38300;115.65922;9.19536;,
 -9.26604;115.65922;9.19536;,
 -9.26604;1.27930;9.19536;,
 8.38300;115.65922;9.19536;,
 8.38300;115.65922;1.48353;,
 -9.26604;115.65922;1.48353;,
 -9.26604;115.65922;9.19536;,
 8.38300;1.27930;1.48353;,
 8.38300;115.65922;1.48353;,
 -9.26604;115.65922;1.48353;,
 -9.26604;1.27930;1.48353;;
 
 27;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;10,12,13,11;,
 4;14,4,15,16;,
 4;17,16,15,1;,
 4;18,19,20,2;,
 4;21,19,18,7;,
 4;22,15,18,23;,
 4;24,25,18,15;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;36,38,39,37;,
 4;40,30,41,42;,
 4;43,42,41,27;,
 4;44,45,46,28;,
 4;47,45,44,33;,
 4;48,41,44,49;,
 4;50,51,44,41;,
 3;52,53,54;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 4;63,64,65,66;,
 4;67,68,69,70;,
 4;67,60,71,72;,
 4;73,74,61,70;;
 
 MeshMaterialList {
  2;
  27;
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
  1,
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
    "data\\TEXTURE\\af18.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000001;1.000000;0.000000;,
  0.000001;-1.000000;-0.000000;,
  -0.358590;0.933495;0.000000;,
  0.358589;0.933496;0.000000;,
  -0.358588;-0.933496;0.000000;,
  0.358589;-0.933496;-0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000001;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.057051;0.000000;0.998371;,
  -0.361115;0.932521;0.000000;,
  0.361113;0.932522;0.000000;,
  -0.016824;-0.999858;0.000000;,
  0.016824;-0.999858;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.019024;0.000000;0.999819;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  27;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,3,3;,
  4;6,3,3,6;,
  4;4,4,7,7;,
  4;8,4,4,8;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;16,16,13,13;,
  4;17,13,13,17;,
  4;14,14,18,18;,
  4;19,14,14,19;,
  4;20,21,21,20;,
  4;20,20,21,21;,
  3;21,15,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;;
 }
 MeshTextureCoords {
  75;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}