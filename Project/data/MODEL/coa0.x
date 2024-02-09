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
 22;
 0.00000;15.79261;-7.75408;,
 5.48297;15.79261;-5.48297;,
 7.32230;2.53863;-7.32230;,
 0.00000;2.53863;-10.35529;,
 7.75408;15.79261;0.00000;,
 10.35529;2.53863;0.00000;,
 5.48297;15.79261;5.48297;,
 7.32230;2.53863;7.32230;,
 0.00000;15.79261;7.75408;,
 0.00000;2.53863;10.35529;,
 -5.48297;15.79261;5.48297;,
 -7.32230;2.53863;7.32230;,
 -7.75408;15.79261;0.00000;,
 -10.35529;2.53863;0.00000;,
 -5.48297;15.79261;-5.48297;,
 -7.32230;2.53863;-7.32230;,
 0.00000;15.79261;-7.75408;,
 0.00000;2.53863;-10.35529;,
 0.00000;24.86095;0.00000;,
 5.48297;15.79261;-5.48297;,
 0.00000;-26.60225;-0.00000;,
 7.32230;2.53863;-7.32230;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,16;,
 3;18,4,19;,
 3;18,6,4;,
 3;18,8,6;,
 3;18,10,8;,
 3;18,12,10;,
 3;18,14,12;,
 3;18,16,14;,
 3;20,17,21;,
 3;20,21,5;,
 3;20,5,7;,
 3;20,7,9;,
 3;20,9,11;,
 3;20,11,13;,
 3;20,13,15;,
 3;20,15,17;;
 
 MeshMaterialList {
  1;
  24;
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
    "data\\TEXTURE\\2601141.jpg";
   }
  }
 }
 MeshNormals {
  23;
  0.659297;0.700535;-0.273090;,
  0.000000;0.438966;-0.898504;,
  0.635338;0.438966;-0.635338;,
  0.898504;0.438966;0.000000;,
  0.635338;0.438966;0.635338;,
  0.000000;0.438966;0.898504;,
  -0.635338;0.438966;0.635338;,
  -0.898504;0.438966;0.000000;,
  -0.635338;0.438966;-0.635338;,
  0.000000;-0.074512;-0.997220;,
  0.705141;-0.074512;-0.705141;,
  0.997220;-0.074512;-0.000000;,
  0.705141;-0.074512;0.705141;,
  0.000000;-0.074512;0.997220;,
  -0.705141;-0.074512;0.705141;,
  -0.997220;-0.074512;0.000000;,
  -0.705141;-0.074512;-0.705141;,
  0.666289;-0.334840;-0.666289;,
  -0.273090;0.700535;0.659297;,
  -0.537425;0.649884;-0.537425;,
  0.666289;-0.334840;0.666289;,
  -0.666289;-0.334840;0.666289;,
  -0.666289;-0.334840;-0.666289;;
  24;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;18,5,4;,
  3;18,6,5;,
  3;18,7,6;,
  3;19,8,7;,
  3;19,1,8;,
  3;17,9,10;,
  3;17,10,11;,
  3;20,11,12;,
  3;20,12,13;,
  3;21,13,14;,
  3;21,14,15;,
  3;22,15,16;,
  3;22,16,9;;
 }
 MeshTextureCoords {
  22;
  0.000000;0.176210;,
  0.125000;0.176210;,
  0.125000;0.433753;,
  0.000000;0.433753;,
  0.250000;0.176210;,
  0.250000;0.433753;,
  0.375000;0.176210;,
  0.375000;0.433753;,
  0.500000;0.176210;,
  0.500000;0.433753;,
  0.625000;0.176210;,
  0.625000;0.433753;,
  0.750000;0.176210;,
  0.750000;0.433753;,
  0.875000;0.176210;,
  0.875000;0.433753;,
  1.000000;0.176210;,
  1.000000;0.433753;,
  0.750000;0.000000;,
  1.125000;0.176210;,
  0.750000;1.000000;,
  1.125000;0.433753;;
 }
}
