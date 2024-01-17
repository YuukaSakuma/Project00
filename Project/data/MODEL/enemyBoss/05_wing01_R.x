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
 12;
 -4.64445;-9.89523;2.44398;,
 -0.06226;15.55725;2.44398;,
 -33.36132;-3.40761;2.44398;,
 -0.06226;15.55725;-2.44398;,
 -33.36132;-3.40761;-2.44398;,
 -4.64445;-9.89523;-2.44398;,
 -0.06226;15.55725;-2.44398;,
 4.95074;-0.92361;-0.39811;,
 -4.64445;-9.89523;-2.44398;,
 4.95074;-0.92361;-0.39811;,
 4.95074;-0.92361;0.48704;,
 -33.36132;-3.40761;-2.44398;;
 
 8;
 3;0,1,2;,
 4;2,1,3,4;,
 3;5,6,7;,
 4;8,9,10,0;,
 4;10,9,3,1;,
 4;8,0,2,4;,
 3;0,10,1;,
 3;11,6,5;;
 
 MeshMaterialList {
  1;
  8;
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
    "data\\TEXTURE\\enemyBoss01.png";
   }
  }
 }
 MeshNormals {
  11;
  0.119869;-0.021580;0.992555;,
  0.682973;-0.730443;-0.000000;,
  0.000000;-0.000000;1.000000;,
  -0.494896;0.868952;0.000000;,
  0.125061;-0.022515;-0.991894;,
  0.248094;-0.044664;-0.967706;,
  0.261735;-0.965140;-0.000000;,
  0.956721;0.291007;0.000000;,
  -0.220363;-0.975418;0.000000;,
  0.237954;-0.042839;0.970331;,
  0.000000;0.000000;-1.000000;;
  8;
  3;0,0,2;,
  4;3,3,3,3;,
  3;4,4,5;,
  4;6,1,1,6;,
  4;7,7,7,7;,
  4;6,6,8,8;,
  3;0,9,0;,
  3;10,4,4;;
 }
 MeshTextureCoords {
  12;
  0.099473;0.547746;,
  0.112321;0.436545;,
  0.018954;0.519402;,
  0.112023;0.436545;,
  0.015893;0.520354;,
  0.260334;0.739847;,
  0.297090;0.470789;,
  0.331802;0.645689;,
  0.099473;0.547746;,
  0.126377;0.508549;,
  0.126377;0.508549;,
  0.047987;0.669669;;
 }
}
