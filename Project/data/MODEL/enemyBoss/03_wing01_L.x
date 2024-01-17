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
 4.45687;-10.18418;-2.36834;,
 -0.13081;15.17581;-2.22418;,
 33.01731;-3.60461;-3.26581;,
 33.01731;-3.60461;-3.26581;,
 -0.13081;15.17581;-2.22418;,
 -0.05555;15.24617;2.65844;,
 33.27651;-3.63847;1.61102;,
 4.55758;-10.25455;2.51347;,
 -5.02244;-1.24586;0.76864;,
 -5.07028;-1.22522;-0.12479;,
 4.45687;-10.18418;-2.36834;,
 -5.07028;-1.22522;-0.12479;;
 
 8;
 3;0,1,2;,
 4;3,4,5,6;,
 3;7,5,8;,
 4;7,8,9,10;,
 4;9,8,5,4;,
 4;7,10,3,6;,
 3;0,11,1;,
 3;6,5,7;;
 
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
  -0.150305;-0.021572;-0.988404;,
  -0.683950;-0.729436;0.011654;,
  -0.031408;-0.000000;-0.999507;,
  0.492364;0.870157;-0.020128;,
  -0.095148;-0.022870;0.995200;,
  -0.220128;-0.045361;0.974416;,
  -0.260668;-0.965420;-0.003973;,
  -0.957682;0.285789;0.034196;,
  0.223897;-0.974434;-0.018665;,
  -0.266990;-0.042826;-0.962747;,
  0.031408;-0.000000;0.999507;;
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
  0.261148;0.739542;,
  0.294691;0.470257;,
  0.048021;0.669676;,
  0.019383;0.516871;,
  0.112148;0.435854;,
  0.112317;0.435854;,
  0.019552;0.516871;,
  0.099478;0.545254;,
  0.126140;0.506606;,
  0.126567;0.506606;,
  0.099905;0.545254;,
  0.332044;0.644411;;
 }
}
