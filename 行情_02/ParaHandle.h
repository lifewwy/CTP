#include "config.h"
#include <iostream>
using namespace std;

void ParaHandle(int argc, char* argv[])
{

	//strcpy_s(INSTRUMENT_ID,argv[1]);

	//char sell_buy[31];
	//strcpy_s( sell_buy, argv[2]); 
	//DIRECTION = sell_buy[0];

	//strcpy_s(CombOffsetFlagType,argv[3]);

	//float limit_price;
	//sscanf_s( argv[4],"%f",&limit_price);
	//LIMIT_PRICE = limit_price;

	//int hands;
	//sscanf_s( argv[5],"%d",&hands);
	//Volume = hands;

	strcpy_s(FRONT_ADDR,argv[1]);
	strcpy_s(BROKER_ID,argv[2]);
	strcpy_s(INVESTOR_ID,argv[3]);
	strcpy_s(PASSWORD,argv[4]);

	int nInstrumentID;
	sscanf_s( argv[5],"%d",&nInstrumentID);
	iInstrumentID = nInstrumentID;	

	for(int i=0;i<iInstrumentID;i++)
	{
		ppInstrumentID[i] = argv[i+6];
	}



	////ppInstrumentID[0] = argv[0];
	//char InstrumentID[132];
	//sscanf_s( argv[5],"%d",&InstrumentID);
	//ppInstrumentID[0] = InstrumentID;

				

	for   (int i   =   0;   i<argc;   i++)  
	{	cout << "-------"<< argv[i] << "-------"  << endl; } 
	
	cout<<endl; // 空行
	cout << "-----------------------------------------"  << endl; 
    cout << "-----------------------------------------"  << endl; 
	cout<<endl; // 空行

	//cout << "-------"<< INSTRUMENT_ID << "-------"  << endl;
	//cout << "-------"<< DIRECTION << "-------"  << endl;
	//cout << "-------"<< CombOffsetFlagType << "-------"  << endl;
	//cout << "-------"<< LIMIT_PRICE << "-------"  << endl;
	//cout << "-------"<< FRONT_ADDR << "-------"  << endl;

	cout << "-------"<< ppInstrumentID[0] << "-------"  << endl;
	cout << "-------"<< iInstrumentID << "-------"  << endl;


	/*argv[k] 转 double,  float, int  等  用 sscanf(),  例如：
	double d;   float f;   int ii;
	sscanf( argv[1],"%lf",&d);
	sscanf( argv[2],"%f",&f);
	sscanf( argv[3],"%d",&ii);*/

	//char ss[80];
	//strcpy( ss, argv[2]);  // 就可以把第k个位置参数传给 s 了。
	//cout << "-------"<< ss << "-------"  << endl;
  
	//INSTRUMENT_ID[0] = 'M';
	
	

	//DIRECTION = '0';
	//DIRECTION = ss[0];
}