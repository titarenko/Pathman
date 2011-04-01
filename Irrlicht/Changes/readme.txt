This folder contains changed sources of Irrlicht 1.7.2.

CXMeshFileLoader.cpp

Initial:
1027: for (u32 j=0; j<mesh.Vertices.size(); ++j)

Changed:
1027: u32 secondCondition = (datasize << 2)/size;
1028: for (u32 j=0; j<mesh.Vertices.size() && j<secondCondition; ++j)

Reason:
Access violation.