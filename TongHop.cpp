#include <fstream>
#include <iostream>
#include <iomanip>
#define nmax 1000
#define abs(x) ((x)<0 ? (-(x)):(x))
using namespace std;

int choice, n, m, d=0, k, a, b;
int s[nmax];
int A[nmax][nmax] = { 0 };     //Khoi tao mang gia tri 0
int dd[]={-2,-2,-1,-1, 1, 1, 2, 2};
int dc[]={ -1, 1,-2, 2,-2, 2,-1, 1};

ifstream filein;
ofstream fileout;

int N_Hau();
void OutputNHau(int k);
int Trienvong(int k);

int TimToHop();
void ToHop();
void BackTracking(int i);
void OutputToHop();

int MaDT();
void NuocDi(int x, int y, int &flag);
void OutputMaDT ();
int DemKhaNang(int a[][nmax], int x, int y);
int KiemTraUuTien(int a[][nmax], int i, int j);

main ()
{
	cout << " ___________________________________________________"<< endl;
	cout << "|            DO AN GIAI THUAT & LAP TRINH           |"<< endl;
	cout << "|            DE TAI: THUAT TOAN QUAY LUI            |"<< endl;
	cout << "|   Giao Vien Huong Dan: Phan Thanh Tao             |"<< endl;
	cout << "|   Sinh Vien Thuc Hien:                            |"<< endl;
	cout << "|   1. Pham Manh Dung  Lop: 17T3  MSSV: 102170149   |"<< endl;
	cout << "|   2. Mai Van Thanh   Lop: 17T3  MSSV: 102170192   |"<< endl;
	cout << "|   Lop HP: 17.Nh12A                                |"<< endl;
	cout << "|___________________________________________________|"<< endl;
	do
	{
		cout << "\n\n Chao ban! Moi lua chon" << endl;
		cout <<"--------------------------------------" << endl;
		cout <<"1.Bai toan N Hau hoa binh" << endl;
		cout <<"2.Bai toan To Hop" << endl;
		cout <<"3.Bai toan Ma Di Tuan" << endl;
		cout <<"0.Ket thuc" << endl;
		cout <<"--------------------------------------" << endl;
		cin >> choice;
		switch (choice)
		{
			case 1: N_Hau();
				break;
			case 2: TimToHop();
				break;
			case 3: MaDT();
				continue;
		}
	}while (choice!=0);
}

int N_Hau()
{
	// Mo va doc du lieu tu file InputNHau.txt
	filein.open("InputNHau.txt");
	filein >> n;
	cout << "So quan hau la: "<< n << endl;
	filein.close();   //Dong file da mo

	// Mo file ghi ket qua OutputNHau.txt
	fileout.open("OutputNHau.txt");
	OutputNHau(1);         // Xep Hau
	fileout.close();   //dong file da mo

	return 0;
}

void OutputNHau (int k)
{
	int i;
	if ( k - 1 == n)
	{
		d++;
		fileout << endl << "Nghiem thu " << d << " la: ";
		cout << endl << "Nghiem thu " << d << " la: ";
		for (i = 1; i <= n; i++)
		{
			fileout << s[i] << "   ";
			cout << s[i] << "   ";
		}
		fileout << endl;
		cout << endl;
	}
	else
	for (i = 1; i <=n; i++)
	{
		s[k] = i;
		if (Trienvong(k)) OutputNHau (k+1);
	}
	//d = 0;
}

int Trienvong (int k)
{
	int i;
	for (i = 1; i < k; i++)
	if (s[k] == s[i] || abs(i-k) == abs(s[i] - s[k])) return 0;
	return 1;
}

int TimToHop()
{
	// Mo va doc du lieu tu file InputToHop.txt
	filein.open("InputToHop.txt");
	filein >> k >> n ;
	cout << "Gia tri cua k va n: "<< k <<" "<< n << endl;
	filein.close();        //Dong file da mo

	// Mo file ghi ket qua OutputToHop.txt
	fileout.open("OutputToHop.txt");
	ToHop();                //Tim to hop
	fileout.close(); 	//dong file da mo

	return 0;
}

void ToHop() //Liet ke cac to hop
{
	if (k>=0 && k<= n)
	{
		s[0] = 0; //khoi tao gia tri a[0]
		cout << "Cac to hop la: \n";
		BackTracking(1);
	}
	else
	{
		cout<<"Loi: Khong thoa dieu kien 0<=k<=n"<<endl;
	}
}

void BackTracking (int i)
{
	for (int j = s[i-1] + 1; j <=n-k+i; j++) // xet cac kha nang cua j
	{
		s[i] = j; // ghi nhan mot gia tri cua j
		if (i == k) // neu cau hinh da du k phan tu
		{
			// in mot cau hinh ra ngoai
			OutputToHop ();
		}
		else
		{
			BackTracking(i+1); // Quay Lui
		}
	}
}

void OutputToHop() // ham de in 1 cau hinh
{
	for (int i = 1; i<=k; i++)
	{
		cout << s[i] << "" ;
		fileout << s[i] << "" ;
	}
	cout << endl;
	fileout << endl;
}

int MaDT()
{
	// Mo va doc du lieu tu file InputMaDT.txt
	filein.open("InputMaDT.txt");
	filein >> n >> a >> b;
	filein.close();	//Dong file da mo

	// Mo file ghi ket qua OutputMaDT.txt
    fileout.open("OutputMaDT.txt");
    int flag = 0;
    d=0;
	NuocDi(a, b, flag); // Ham nuoc di cua quan ma
	if(!flag)
	{
		//Neu khong tim duoc duong di thi se thong bao
		cout <<"Khong tim thay duong di";
		fileout <<"Khong tim thay duong di";
	}
	fileout.close();	//Dong file da mo
}

void NuocDi(int x, int y, int &flag)
{
	++ d; //Tang gia tri buoc di
	A[x][y] = d; //Danh dau da di
	//Kiem tra xem quan ma da di het ban co chua
    
	if (d == n*n)
	{
			cout << "Cac buoc di la: \n";
			fileout <<"Cac buoc di la: \n";
			OutputMaDT();
			flag = 1;
	}
    if(KiemTraUuTien(A,x,y)!=-1 && flag!=1){
		//Neu chua di het ban co thi tao nuoc di moi
		//Tao vi tri x, y moi
		int pos = KiemTraUuTien(A,x,y);
		int u = x + dd[pos], v = y + dc[pos];
		      NuocDi(u, v, flag);
	}
		

	//Neu khong tim duoc buoc di thi tra lai cac gia tri ban dau
	-- d;
	A[x][y] = 0;
}

void OutputMaDT ()
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout <<setw(4) << A[i][j];
			fileout <<setw(4) << A[i][j];
		}
		cout << endl;
		fileout << "\n" ;
	}
	cout<<endl;
	fileout<<"\n";
}

int DemKhaNang(int a[][nmax], int x, int y){
	int count = 0; 
    for (int i = 0; i < 8; ++i) {
		int u = x + dd[i], v = y + dc[i];
        if (u>=0 && u<n && v>=0 && v<n && a[u][v] == 0) 
            count++; 
}
    return count; 
}

int KiemTraUuTien(int a[][nmax], int x, int y){
		
	int min = 9, b, min_i = -1;
	
	for(int i=0; i<8; i++){
		if(a[x][y]==63){
				int u = x + dd[i], v = y + dc[i];
	     if (u>=0 && u<n && v>=0 && v<n && a[u][v] == 0) 
	      return i;

		 }
		 else{
     	   int u = x + dd[i], v = y + dc[i];
	       if (u>=0 && u<n && v>=0 && v<n && a[u][v] == 0) {
           b = DemKhaNang(a, u, v);
           if(b<min && b!=0) {
    	      min = b;
              min_i = i;
         	}
           }
        }
   }
    return min_i;
   
}


