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
 -0.43224;1.46084;0.26450;,
 -0.43224;-0.71658;-0.56859;,
 -2.10105;-0.71658;-0.56859;,
 -2.10105;1.46084;0.26450;,
 -0.43224;-0.68452;5.87172;,
 -8.21508;-3.57459;13.42536;,
 -0.43224;-2.86193;5.03862;,
 -8.21508;-5.75200;12.59227;,
 7.48015;-5.75200;12.59227;,
 1.03336;-0.71658;-0.56859;,
 1.03336;1.46084;0.26450;,
 7.48015;-3.57459;13.42536;;
 
 10;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,4,5,7;,
 4;1,6,7,2;,
 4;2,7,5,3;,
 4;8,9,10,11;,
 4;9,8,6,1;,
 4;8,11,4,6;,
 4;11,10,0,4;,
 4;10,9,1,0;;
 
 MeshMaterialList {
  1;
  10;
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
    "data\\TEXTURE\\enemyBoss01.png";
   }
  }
 }
 MeshNormals {
  12;
  0.909351;0.148665;-0.388561;,
  0.000000;0.357342;-0.933974;,
  0.000000;0.933973;0.357344;,
  0.720555;-0.247783;0.647615;,
  0.000000;0.357342;-0.933974;,
  0.000000;0.933973;0.357344;,
  0.000000;-0.933973;-0.357343;,
  0.000000;-0.933973;-0.357343;,
  -0.917370;0.142235;-0.371755;,
  -0.000000;-0.933973;-0.357343;,
  -0.714809;-0.249898;0.653145;,
  -0.000000;0.933973;0.357344;;
  10;
  4;4,4,1,1;,
  4;5,5,2,2;,
  4;3,3,3,3;,
  4;6,6,7,7;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;9,9,6,6;,
  4;10,10,10,10;,
  4;11,11,5,5;,
  4;4,4,4,4;;
 }
 MeshTextureCoords {
  12;
  0.125458;0.959057;,
  0.125458;0.968879;,
  0.147741;0.968879;,
  0.147741;0.959057;,
  0.125458;0.892951;,
  0.229380;0.803896;,
  0.125458;0.902773;,
  0.229380;0.813718;,
  0.019805;0.813718;,
  0.105888;0.968879;,
  0.105888;0.959057;,
  0.019805;0.803896;;
 }
}
