#include "Obj2.h"
Obj2::Obj2(char * fileName)
{
	this->file = fileName;
	string line;
	v = false;
	vt = false;
	vn = false;

	//creates a read/wrie files stream 
	ifstream myfile(file);

	while (!myfile.eof())
	{
		//returns each line of the file storing in a variable
		getline(myfile, line);

		//reads in only the lines that start with "v"
		if (line[0] == 'v' && line[1] == ' ')
		{
			v = true;
		}
		if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
		{
			vt = true;
		}
		if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
		{
			vn = true;
		}
	}
}
Obj2::~Obj2()
{


}

void Obj2::loadV()
{
	if (v == true)
	{
		string line;
		string v;
		vType x = 0;
		vType y = 0;
		vType z = 0;

		//creates a read/wrie files stream 
		ifstream myfile(file);

		while (!myfile.eof())
		{
			//returns each line of the file storing in a variable
			getline(myfile, line);

			//reads in only the lines that start with "v"
			if (line[0] == 'v' && line[1] == ' ')
			{
				//myfile >> v[n] >> valuesX[n] >> valuesY[n] >> valuesZ[n];
				//keeps the contens of the previos line when accessing another one
				istringstream inputS(line);
				inputS >> v >> x >> y >> z;
				V.push_back(x);
				V.push_back(y);
				V.push_back(z);
				x = 0;
				y = 0;
				z = 0;

			}


		}
	}
	else
	{
		cout << "cant print, does not contain vertex info." << endl;
	}
}
void Obj2::printV()
{
	if (v == true)
	{
		//print vertex info
		for (unsigned int i = 0; i < V.size() - 1; i = i + 3)
		{
			cout << "v ";
			cout << V[i] << ", ";
			cout << V[i + 1] << ", ";
			cout << V[i + 2];
			cout << endl;
		}
		//cout << vertex[vertex.capacity()];
	}
	else
	{
		cout << "cant print, does not contain vertex info." << endl;
	}
}

void Obj2::loadVT()
{
	if (vt == true)
	{
		string line;
		string vt;
		vType x = 0;
		vType y = 0;

		//creates a read/wrie files stream 
		ifstream myfile(file);

		while (!myfile.eof())
		{
			//returns each line of the file storing in a variable
			getline(myfile, line);

			//reads in only the lines that start with "v"
			if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
			{
				//myfile >> v[n] >> valuesX[n] >> valuesY[n] >> valuesZ[n];
				//keeps the contens of the previos line when accessing another one
				istringstream inputS(line);
				inputS >> vt >> x >> y;
				VT.push_back(x);
				VT.push_back(y);
				x = 0;
				y = 0;

			}


		}
	}
	else
	{
		cout << "does not contain vertex texture information." << endl;
	}
}
void Obj2::printVT()
{
	if (vt == true)
	{
		//print vertex info
		for (unsigned int i = 0; i < VT.size() - 1; i = i + 2)
		{
			cout << "vt ";
			cout << VT[i] << ", ";
			cout << VT[i + 1];
			cout << endl;
		}
	}
	else
	{
		cout << "cant print, does not contain vertex texture information." << endl;
	}

}

void Obj2::loadVN()
{
	if (vn == true)
	{
		string line;
		string vn;
		vType x = 0;
		vType y = 0;
		vType z = 0;

		//creates a read/wrie files stream 
		ifstream myfile(file);

		while (!myfile.eof())
		{
			//returns each line of the file storing in a variable
			getline(myfile, line);

			//reads in only the lines that start with "v"
			if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			{
				//myfile >> v[n] >> valuesX[n] >> valuesY[n] >> valuesZ[n];
				//keeps the contens of the previos line when accessing another one
				istringstream inputS(line);
				inputS >> vn >> x >> y >> z;
				VN.push_back(x);
				VN.push_back(y);
				VN.push_back(z);
				x = 0;
				y = 0;
				z = 0;

			}
		}
	}
	else
	{
		cout << "does not contain vertex normal information." << endl;
	}
}
void Obj2::printVN()
{
	if (vn == true)
	{
		//print vertex info
		for (unsigned int i = 0; i < VN.size() - 1; i = i + 3)
		{
			cout << "vn ";
			cout << VN[i] << ", ";
			cout << VN[i + 1] << ", ";
			cout << VN[i + 2];
			cout << endl;
		}
		//cout << vertex[vertex.capacity()];
	}
	else
	{
		cout << "cant print, does not contain vertex normal information." << endl;
	}
}



void Obj2::loadF()
{
	string line;
	char f;
	//int k;
	int tempfV[4];
	int tempfVT[4];
	int tempfVN[4];
	//creates a read/wrie files stream 
	ifstream myfile(file);

	while (!myfile.eof())
	{
		//returns each line of the file storing in a variable
		getline(myfile, line);

		if (line == "") continue;

		//reads in only the lines that start with "v"
		if (v == true && vt == true && vn == true)
		{
			if (line[0] == 'f' && line[1] == ' ')
			{
				face tempFace;
				istringstream inputS(line);

				int nG = numberGaps(line);
				//cout << nG << endl;
				if (nG == 3)
				{
					inputS >> f >> tempfV[0] >> f >> tempfVT[0] >> f >> tempfVN[0] >> tempfV[1] >> f >> tempfVT[1] >> f >> tempfVN[1] >> tempfV[2] >> f >> tempfVT[2] >> f >> tempfVN[2];
					tempFace.quad = false;
				}
				if (nG == 4)
				{
					inputS >> f >> tempfV[0] >> f >> tempfVT[0] >> f >> tempfVN[0]    >>     tempfV[1] >> f >> tempfVT[1] >> f >> tempfVN[1]    >>    tempfV[2] >> f >> tempfVT[2] >> f >> tempfVN[2]    >>   tempfV[3] >> f >> tempfVT[3] >> f >> tempfVN[3];
					tempFace.quad = true;
				}
				
				for (int x = 0; x < nG; x++)
				{
					tempFace.fV.push_back(tempfV[x]);
					tempfV[x] = 0;
				}

				for (int x = 0; x < nG; x++)
				{
					tempFace.fVT.push_back(tempfVT[x]);
					tempfVT[x] = 0;
				}
				for (int x = 0; x < nG; x++)
				{
					tempFace.fVN.push_back(tempfVN[x]);
					tempfVN[x] = 0;
				}

				F.push_back(tempFace);
			}
		}

		//==================================================
		if (v == true && vt == true && vn == false)
		{
			if (line[0] == 'f' && line[1] == ' ')
			{
				face tempFace;
				istringstream inputS(line);
				int nG = numberGaps(line);
				if (nG == 3)
				{
					inputS >> f >> tempfV[0] >> f >> tempfVT[0] >> tempfV[1] >> f >> tempfVT[1] >> tempfV[2] >> f >> tempfVT[2];
					tempFace.quad = false;
				}

				if (nG == 4)
				{
					inputS >> f >> tempfV[0] >> f >> tempfVT[0] >> tempfV[1] >> f >> tempfVT[1] >> tempfV[2] >> f >> tempfVT[2] >> tempfV[3] >> f >> tempfVT[3];
					tempFace.quad = true;
				}


				for (int x = 0; x < nG; x++)
				{
					tempFace.fV.push_back(tempfV[x]);
					tempfV[x] = 0;
				}

				for (int x = 0; x < nG; x++)
				{
					tempFace.fVT.push_back(tempfVT[x]);
					tempfVT[x] = 0;
				}
				F.push_back(tempFace);
			}
		}
		//======================================================
		if (v == true && vt == false && vn == true)
		{
			if (line[0] == 'f' && line[1] == ' ')
			{
				face tempFace;
				istringstream inputS(line);
				int nG = numberGaps(line);
				if (nG == 3)
				{
					inputS >> f >> tempfV[0] >> f >> f >> tempfVN[0] >> tempfV[1] >> f >> f >> tempfVN[1] >> tempfV[2] >> f >> f >> tempfVN[2];
					tempFace.quad = false;
				}

				if (nG == 4)
				{
					inputS >> f >> tempfV[0] >> f >> f >> tempfVN[0] >> tempfV[1] >> f >> f >> tempfVN[1] >> tempfV[2] >> f >> f >> tempfVN[2] >> tempfV[3] >> f >> f >> tempfVN[3];
					tempFace.quad = true;
				}

				for (int x = 0; x < nG; x++)
				{
					tempFace.fV.push_back(tempfV[x]);
					tempfV[x] = 0;
				}

				for (int x = 0; x < nG; x++)
				{
					tempFace.fVN.push_back(tempfVN[x]);
					tempfVN[x] = 0;
				}
				F.push_back(tempFace);
			}
		}

		//===========================================================
		if (v == true && vt == false && vn == false)
		{
			if (line[0] == 'f' && line[1] == ' ')
			{
				face tempFace;
				istringstream inputS(line);
				int nG = numberGaps(line);
				if (nG == 3)
				{
					inputS >> f >> tempfV[0] >> tempfV[1] >> tempfV[2];
					tempFace.quad = false;
				}
				
				if (nG == 4)
				{
					inputS >> f >> tempfV[0] >> tempfV[1] >> tempfV[2] >> tempfV[3];
					tempFace.quad = true;
				}

				for (int x = 0; x < nG; x++)
				{
					tempFace.fV.push_back(tempfV[x]);
					tempfV[x] = 0;
				}
				F.push_back(tempFace);
			}
		}



	}

}

void Obj2::printF()
{
	if (v == true && vt == true && vn == true)
	{
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << ", " << F[i].fV[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << endl;
			}
		}
		//=================================
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fVT " << F[i].fVT[0] << ", " << F[i].fVT[1] << ", " << F[i].fVT[2] << ", " << F[i].fVT[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fVT " << F[i].fVT[0] << ", " << F[i].fVT[1] << ", " << F[i].fVT[2] << endl;
			}
		}
		//=================================
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fVN " << F[i].fVN[0] << ", " << F[i].fVN[1] << ", " << F[i].fVN[2] << ", " << F[i].fVN[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fVN " << F[i].fVN[0] << ", " << F[i].fVN[1] << ", " << F[i].fVN[2] << endl;
			}
		}

	}
	//=====================================================================
	if (v == true && vt == true && vn == false)
	{
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << ", " << F[i].fV[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << endl;
			}
		}
		//=================================
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fVT " << F[i].fVT[0] << ", " << F[i].fVT[1] << ", " << F[i].fVT[2] << ", " << F[i].fVT[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fVT " << F[i].fVT[0] << ", " << F[i].fVT[1] << ", " << F[i].fVT[2] << endl;
			}
		}

	}
	//=====================================================================
	if (v == true && vt == false && vn == true)
	{
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << ", " << F[i].fV[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << endl;
			}
		}
		//=================================
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fVN " << F[i].fVN[0] << ", " << F[i].fVN[1] << ", " << F[i].fVN[2] << ", " << F[i].fVN[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fVN " << F[i].fVN[0] << ", " << F[i].fVN[1] << ", " << F[i].fVN[2] << endl;
			}
		}
	}
	//=====================================================================
	if (v == true && vt == false && vn == false)
	{
		for (int i = 0; i < F.size(); i++)
		{
			if (F[i].quad == true)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << ", " << F[i].fV[3] << endl;
			}
			else if (F[i].quad == false)
			{
				cout << "fV " << F[i].fV[0] << ", " << F[i].fV[1] << ", " << F[i].fV[2] << endl;
			}
		}
		//=================================
	}

}


void Obj2::convertVertexRTE()
{
	if (v == true)
	{
		
		int fNum = 0;
		
		for (unsigned int i = 0; i < F.size() ; i++)
		{

			//dont triangulate
			if (F[i].quad == false)
			{
				for (unsigned int x = 0; x < 3; x++)
				{
					int index = (F[i].fV[x] - 1) * 3;

					VRTE.push_back(V[index]);
					VRTE.push_back(V[index + 1]);
					VRTE.push_back(V[index + 2]);
				}

			}
			//triangulate
			if (F[fNum].quad == true)
			{
				vType tempVert[4][3];
				for (unsigned int x = 0; x < 4; x++)
				{
					int index = (F[i].fV[x] - 1) * 3;

					tempVert[x][0] = V[index];
					tempVert[x][1] = V[index + 1];
					tempVert[x][2] = V[index + 2];
				}
				/*for (unsigned int m = 0; m < 3; m++)
				{
					for (unsigned int d = 0; d < 3; d++)
					{
						VRTE.push_back(tempVert[m][d]);
					}
				}

				for (unsigned int m = 1; m < 4; m++)
				{
					for (unsigned int d = 0; d < 3; d++)
					{
						VRTE.push_back(tempVert[m][d]);
					}
				}*/
				for (unsigned int d = 0; d < 3; d++)
				{
					VRTE.push_back(tempVert[0][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VRTE.push_back(tempVert[1][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VRTE.push_back(tempVert[2][d]);
				}

				for (unsigned int d = 0; d < 3; d++)
				{
					VRTE.push_back(tempVert[2][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VRTE.push_back(tempVert[3][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VRTE.push_back(tempVert[0][d]);
				}
			

			}
			


			fNum++;
		}
	}
	else
	{
		cout << "Cant convert to RTE, No vertex info." << endl;
	}
}
//
void Obj2::printVertexRTE()
{
	int someConst = 0;
	for (unsigned int i = 0; i < VRTE.size() ; i = i + 3)
	{
		someConst++;
			cout << "VRTE ";
			cout << VRTE[i] << ", ";
			cout << VRTE[i + 1] << ", ";
			cout << VRTE[i + 2];
			cout << endl;
			if (someConst>2)
			{
				cout << endl;
				someConst = 0;
			}
		//cout << i << endl;
	}
}


void Obj2::convertVertexTextureRTE()
{
	if (vt == true)
	{

		int fNum = 0;

		for (unsigned int i = 0; i < F.size(); i++)
		{

			//dont triangulate
			if (F[i].quad == false)
			{
				for (unsigned int x = 0; x < 3; x++)
				{
					int index = (F[i].fVT[x] - 1) * 2;

					VTRTE.push_back(VT[index]);
					VTRTE.push_back(1.0f - VT[index + 1]);
				}

			}
			//triangulate
			if (F[fNum].quad == true)
			{
				vType tempVertTexture[4][2];
				for (unsigned int x = 0; x < 4; x++)
				{
					int index = (F[i].fVT[x] - 1) * 2;

					tempVertTexture[x][0] = VT[index];
					tempVertTexture[x][1] = VT[index + 1];
				}
				/*for (unsigned int m = 0; m < 3; m++)
				{
				for (unsigned int d = 0; d < 3; d++)
				{
				VRTE.push_back(tempVert[m][d]);
				}
				}

				for (unsigned int m = 1; m < 4; m++)
				{
				for (unsigned int d = 0; d < 3; d++)
				{
				VRTE.push_back(tempVert[m][d]);
				}
				}*/
				for (unsigned int d = 0; d < 2; d++)
				{
					VTRTE.push_back(tempVertTexture[0][d]);
				}
				for (unsigned int d = 0; d < 2; d++)
				{
					VTRTE.push_back(tempVertTexture[1][d]);
				}
				for (unsigned int d = 0; d < 2; d++)
				{
					VTRTE.push_back(tempVertTexture[2][d]);
				}

				for (unsigned int d = 0; d < 2; d++)
				{
					VTRTE.push_back(tempVertTexture[2][d]);
				}
				for (unsigned int d = 0; d < 2; d++)
				{
					VTRTE.push_back(tempVertTexture[3][d]);
				}
				for (unsigned int d = 0; d < 2; d++)
				{
					VTRTE.push_back(tempVertTexture[0][d]);
				}


			}



			fNum++;
		}
	}
	else
	{
		cout << "Cant convert to RTE, No vertex texture info." << endl;
	}
}

void Obj2::printVertexTextureRTE()
{
	int someConst = 0;
	for (unsigned int i = 0; i < VTRTE.size(); i = i + 2)
	{
		someConst++;
		cout << "VTRTE ";
		cout << VTRTE[i] << ", ";
		cout << VTRTE[i + 1];
		cout << endl;
		if (someConst>2)
		{
			cout << endl;
			someConst = 0;
		}
		//cout << i << endl;
	}
}

void Obj2::convertVertexNormalRTE()
{
	if (vn == true)
	{

		int fNum = 0;
		for (unsigned int i = 0; i < F.size(); i++)
		{

			//dont triangulate
			if (F[i].quad == false)
			{
				for (unsigned int x = 0; x < 3; x++)
				{
					int index = (F[i].fVN[x] - 1) * 3;

					VNRTE.push_back(VN[index]);
					VNRTE.push_back(VN[index + 1]);
					VNRTE.push_back(VN[index + 2]);
				}

			}
			//triangulate
			if (F[fNum].quad == true)
			{
				vType tempVertNorm[4][3];
				for (unsigned int x = 0; x < 4; x++)
				{
					int index = (F[i].fVN[x] - 1) * 3;

					tempVertNorm[x][0] = VN[index];
					tempVertNorm[x][1] = VN[index + 1];
					tempVertNorm[x][2] = VN[index + 2];
				}
				/*for (unsigned int m = 0; m < 3; m++)
				{
				for (unsigned int d = 0; d < 3; d++)
				{
				VRTE.push_back(tempVert[m][d]);
				}
				}

				for (unsigned int m = 1; m < 4; m++)
				{
				for (unsigned int d = 0; d < 3; d++)
				{
				VRTE.push_back(tempVert[m][d]);
				}
				}*/
				for (unsigned int d = 0; d < 3; d++)
				{
					VNRTE.push_back(tempVertNorm[0][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VNRTE.push_back(tempVertNorm[1][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VNRTE.push_back(tempVertNorm[2][d]);
				}

				for (unsigned int d = 0; d < 3; d++)
				{
					VNRTE.push_back(tempVertNorm[2][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VNRTE.push_back(tempVertNorm[3][d]);
				}
				for (unsigned int d = 0; d < 3; d++)
				{
					VNRTE.push_back(tempVertNorm[0][d]);
				}


			}



			fNum++;
		}
	}
	else
	{
		cout << "Cant convert to RTE, No vertex normal info." << endl;
	}
}

void Obj2::printVertexNormalRTE()
{
	int someConst = 0;
	for (unsigned int i = 0; i < VNRTE.size(); i = i + 3)
	{
		someConst++;
		cout << "VNRTE ";
		cout << VNRTE[i] << ", ";
		cout << VNRTE[i + 1] << ", ";
		cout << VNRTE[i + 2];
		cout << endl;
		if (someConst>2)
		{
			cout << endl;
			someConst = 0;
		}
		//cout << i << endl;
	}
}

//============PUBLIC mehtods=================
void Obj2::loadAll()
{
	loadV();
	loadVT();
	loadVN();
	loadF();
}

void Obj2::printAll()
{
	printV();
	printVT();
	printVN();
	printF();
}

int Obj2::numberGaps(string l)
{
	int q = 0;
	for (int i = 0; i < l.size();i++)
	{
		//cout << l[i];
		if (l[i] == ' ' )
		{
			q++;
		}

	}
	//cout << q << endl;;
	return q;
}

void Obj2::convertoObjToGlm()
{
	if (v == true)
	{
		for (int i = 0; i < VRTE.size(); i += 3)
		{
			glm::vec3 tempVert;
			tempVert.x = VRTE[i + 0];
			tempVert.y = VRTE[i + 1];
			tempVert.z = VRTE[i + 2];
			vertices.push_back(tempVert);
		}
	}

	if (vt == true)
	{

		for (int i = 0; i < VTRTE.size(); i += 2)
		{
			glm::vec2 tempUV;
			tempUV.x = VTRTE[i + 0];
			tempUV.y = VTRTE[i + 1];
			uvs.push_back(tempUV);
		}
	}

	if (vn == true)
	{
		for (int i = 0; i < VNRTE.size(); i += 3)
		{
			glm::vec3 tempNormal;
			tempNormal.x = VNRTE[i + 0];
			tempNormal.y = VNRTE[i + 1];
			tempNormal.z = VNRTE[i + 2];
			normals.push_back(tempNormal);
		}
	}

}

void Obj2::computeTangentBasis()
{
	for (unsigned int i = 0; i<vertices.size(); i += 3){

		// Shortcuts for vertices
		glm::vec3 & v0 = vertices[i + 0];
		glm::vec3 & v1 = vertices[i + 1];
		glm::vec3 & v2 = vertices[i + 2];

		// Shortcuts for UVs
		glm::vec2 & uv0 = uvs[i + 0];
		glm::vec2 & uv1 = uvs[i + 1];
		glm::vec2 & uv2 = uvs[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later, in vboindexer.cpp
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		// Same thing for binormals
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}

	// See "Going Further"
	for (unsigned int i = 0; i<vertices.size(); i += 1)
	{
		glm::vec3 & n = normals[i];
		glm::vec3 & t = tangents[i];
		glm::vec3 & b = bitangents[i];

		// Gram-Schmidt orthogonalize
		t = glm::normalize(t - n * glm::dot(n, t));

		// Calculate handedness
		if (glm::dot(glm::cross(n, t), b) < 0.0f){
			t = t * -1.0f;
		}

	}
}



