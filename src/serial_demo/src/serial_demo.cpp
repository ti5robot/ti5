//serial_demo.cpp
#include <ros/ros.h>
#include <serial/serial.h>
#include <iostream>


#include "std_msgs/String.h"

#include <sensor_msgs/JointState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <iostream>
#define MESSAGE_FREQ 100
#define MESSAGE_FREQ_END 60


double next_velocitie[6]={0};

double ori_velocitie[6]={0} ;
double cha_velocitie[6]={0} ;
double now_velocitie[6]={0} ;

double next_position[6]={0};

double ori_position[6]={0} ;
double cha_position[6]={0} ;
double now_position[6]={0} ;
char buffer[5120];
int t1=0;
int t2=0;
int t3=0;
int t4=0;
int t5=0;
int t6=0;


int    r1[500]={0};
int    r2[500]={0};
int    r3[500]={0};

int    r4[500]={0};
int    r5[500]={0};
int    r6[500]={0};





class Listener {
private:
    char topic_message[2048] = { 0 };
public:
    //void callback(const sensor_msgs::JointState::ConstPtr &msg);
    void callback(const moveit_msgs::DisplayTrajectory::ConstPtr &msg);
    char* getMessageValue();
};



int32_t crc32_table[256]={0,1996959894,-301047508,-1727442502,124634137,1886057615,-379345611,-1637575261,	249268274,2044508324,-522852066,-1747789432,162941995,2125561021,-407360249,-1866523247,498536548,1789927666,-205950648,-2067906082,450548861,1843258603,-187386543,-2083289657,325883990,1684777152,-43845254,-1973040660,	335633487,1661365465,-99664541,-1928851979,997073096,1281953886,-715111964,-1570279054,1006888145,1258607687,-770865667,-1526024853,901097722,1119000684,-608450090,-1396901568,853044451,1172266101,-589951537,-1412350631,	651767980,1373503546,-925412992,-1076862698,565507253,1454621731,-809855591,-1195530993,671266974,1594198024,-972236366,-1324619484,795835527,1483230225,-1050600021,-1234817731,1994146192,31158534,-1731059524,-271249366,	1907459465,112637215,-1614814043,-390540237,2013776290,251722036,-1777751922,-519137256,2137656763,141376813,-1855689577,-429695999,1802195444,476864866,-2056965928,-228458418,1812370925,453092731,-2113342271,-183516073,	1706088902,314042704,-1950435094,-54949764,1658658271,366619977,-1932296973,-69972891,1303535960,984961486,-1547960204,-725929758,1256170817,1037604311,-1529756563,-740887301,1131014506,879679996,-1385723834,-631195440,	1141124467,855842277,-1442165665,-586318647,1342533948,654459306,-1106571248,-921952122,1466479909,544179635,-1184443383,-832445281,1591671054,702138776,-1328506846,-942167884,1504918807,783551873,-1212326853,-1061524307,-306674912,-1698712650,62317068,1957810842,-355121351,-1647151185,81470997,1943803523,-480048366,-1805370492,225274430,2053790376,-468791541,-1828061283,167816743,2097651377,-267414716,-2029476910,503444072,1762050814,-144550051,-2140837941,426522225,1852507879,-19653770,-1982649376,282753626,1742555852,-105259153,-1900089351,397917763,1622183637,-690576408,-1580100738,953729732,1340076626,-776247311,-1497606297,1068828381,1219638859,-670225446,-1358292148,906185462,1090812512,-547295293,-1469587627,829329135,1181335161,-882789492,-1134132454,628085408,1382605366,-871598187,-1156888829,570562233,1426400815,-977650754,-1296233688,733239954,1555261956,-1026031705,-1244606671,752459403,1541320221,-1687895376,-328994266,1969922972,40735498,-1677130071,-351390145,1913087877,83908371,-1782625662,-491226604,2075208622,213261112,-1831694693,-438977011,2094854071,198958881,-2032938284,-237706686,1759359992,534414190,-2118248755,-155638181,1873836001,414664567,-2012718362,-15766928,1711684554,285281116,-1889165569,-127750551,1634467795,376229701,-1609899400,-686959890,1308918612,956543938,-1486412191,-799009033,1231636301,1047427035,-1362007478,-640263460,1088359270,936918000,-1447252397,-558129467,1202900863,817233897,-1111625188,-893730166,1404277552,615818150,-1160759803,-841546093,1423857449,601450431,-1285129682,-1000256840,1567103746,711928724,-1274298825,-1022587231,1510334235,755167117};

int16_t table_s[]={12336,12592,12848,13104,13360,13616,13872,14128,14384,14640,16688,16944,17200,17456,17712,17968,12337,12593,12849,13105,13361,13617,13873,14129,14385,14641,16689,16945,17201,17457,17713,17969,12338,12594,12850,13106,13362,13618,13874,14130,14386,14642,16690,16946,17202,17458,17714,17970,12339,12595,12851,13107,13363,13619,13875,14131,14387,14643,16691,16947,17203,17459,17715,17971,12340,12596,12852,13108,13364,13620,13876,14132,14388,14644,16692,16948,17204,17460,17716,17972,12341,12597,12853,13109,13365,13621,13877,14133,14389,14645,16693,16949,17205,17461,17717,17973,12342,12598,12854,13110,13366,13622,13878,14134,14390,14646,16694,16950,17206,17462,17718,17974,12343,12599,12855,13111,13367,13623,13879,14135,14391,14647,16695,16951,17207,17463,17719,17975,12344,12600,12856,13112,13368,13624,13880,14136,14392,14648,16696,16952,17208,17464,17720,17976,12345,12601,12857,13113,13369,13625,13881,14137,14393,14649,16697,16953,17209,17465,17721,17977,12353,12609,12865,13121,13377,13633,13889,14145,14401,14657,16705,16961,17217,17473,17729,17985,12354,12610,12866,13122,13378,13634,13890,14146,14402,14658,16706,16962,17218,17474,17730,17986,12355,12611,12867,13123,13379,13635,13891,14147,14403,14659,16707,16963,17219,17475,17731,17987,12356,12612,12868,13124,13380,13636,13892,14148,14404,14660,16708,16964,17220,17476,17732,17988,12357,12613,12869,13125,13381,13637,13893,14149,14405,14661,16709,16965,17221,17477,17733,17989,12358,12614,12870,13126,13382,13638,13894,14150,14406,14662,16710,16966,17222,17478,17734,17990};

char* Listener::getMessageValue() {
    return topic_message;
}



serial::Serial sp;
size_t MemToStrStream(char* dest, const char* sourse, uint32_t size,char head,char end)
{
    uint32_t i = 0;
    uint8_t *pindex = (uint8_t *)sourse;
    *dest = head;
    int16_t *p = (int16_t *)(dest+1);
    for(i=0;i<size;i++)
    {
        p[i] = table_s[pindex[i]];
    }
    p[i] = end;
    //    qDebug()<<"end:"<<dest[size*2+1]<<dest[size*2+2];
    //    printf("**%d**%d**,",dest[size*2+1],dest[size*2+2]);
    return size*2+2;
}


int string_to_hex(const std::string& input)
{
	std::string lut = "0123456789ABCDEF";
	        int len = input.length();

		int  output=0;
		//output.reserve(2 * len);
		for (int i = 0; i < len; ++i)
		   {
		 const unsigned char c = input[i];
		 int m =lut.find(c);
			 if(i==0){
                 output = output+m*16;}
			 else{output = output+m;}
		    }
		 return output;
}






uint32_t calcCRC32(uint32_t crc, uint8_t *string, uint32_t size)
{
    while(size--)
        crc = (crc >> 8)^(crc32_table[(crc ^ *string++)&0xff]);
    return crc;
}



void bufferTransfor(const std::string& buffer )
{
	//std::cout<<buffer<<std::endl;
	std::string::size_type position;
	//position=buffer.find("\n");
	//std::cout<<"length:"<<buffer.length()<<std::endl;
	//std::cout<<"index:"<<position<<std::endl;
	//std::cout<<"text:"<<buffer<<std::endl;

	int index = buffer.find("\n");
		uint8_t mem[400]={0},memIndex=0;

		int32_t parameterList[10]={0};
		uint8_t canIdList[10]={0},cmd[10]={0};
	if (index>1 )
	{//1

		//std::cout<<buffer<<std::endl;
		std::string frame = buffer.substr(1,index-1);
		while (true)
		{
			if(frame.length()>1)
			{
	        std::string t1 = frame.substr(0,2);
		mem[memIndex] = string_to_hex(t1);//2位16进制
		//std::cout<<t1<<std::endl;
		//std::cout<<mem[memIndex]<<std::endl;	
		memIndex++;
	        frame.erase(0,2);
	        //std::cout <<frame<<std::endl;
			}
			else{
                            uint8_t *pCanId = mem+1;
			    uint8_t *pCommand = mem+7+1;
			    uint8_t *pParameter = mem+7+7+1;

			    for(int i=0;i<7;i++)
			    {
		             canIdList[i]=mem[i+1];
                             parameterList[i]=mem[i*4+7*2+1];
			    //std::cout<<"id"<<canIdList[i]<<"parameter"<<parameterList[i]<<std::endl;
			    }

			    break;
			}

		}
		//std::cout<<"break"<<std::endl;
		//mem[memIndex]=
		//std::cout<<frame<<std::endl;


	}//1


}


 
int32_t sendCommand(uint8_t numOfActuator, uint8_t *canIdList, uint8_t *commandList, uint32_t *parameterList)
{
    
    uint8_t buf[400],index=0;
    buf[index++] = numOfActuator;
    if(numOfActuator==0)
    {
        buf[index++] = canIdList[0];
        buf[index++] = commandList[0];
        buf[index] = parameterList[0];
        index +=4;
    }
    else
    {
        for(int i=0;i<numOfActuator;i++)
        {
            buf[index++] = canIdList[i];
        }
        for(int i=0;i<numOfActuator;i++)
        {
            buf[index++] = commandList[i];
        }
        for(int i=0;i<numOfActuator;i++)
        {

            *(uint32_t *)(buf+index) = parameterList[i];
            index+=4;
        }
    }

    *(uint32_t *)(buf+index) = calcCRC32(0,buf,index);
    index+=4;
    char uartTxBuf[2000];

    //the first title of char
    uint32_t byteToWrite = MemToStrStream(uartTxBuf,(char*)buf,index,'<','\n');

    size_t writeSize=0;
    //std::cout<<sp.write(uartTxBuf) <<std::endl;
    //maybe the size is 24 maybe 48 or 72
    if(sp.write(uartTxBuf)==24)
    {
	    //std::cout<<uartTxBuf<<std::endl;
    }
    if(sp.write(uartTxBuf)==48)
    {
	    //std::cout<<uartTxBuf<<std::endl;
    }

   //std::cout<<uartTxBuf<<std::endl;
   //bool e123 =sp.write(uartTxBuf); 

}


void Listener::callback(const moveit_msgs::DisplayTrajectory::ConstPtr &msg) {
    int n = msg->trajectory[0].joint_trajectory.points.size();
    int cn[6];
    char str[5120];
    char str123[5120];
    float ww;
    float vv;
    float zs;
    float zs1;
    float zss =1.0;
    std::string end_position ="";

 for (int i = 0; i < n-1; i++) {
		        usleep(3000);
        ori_position[0]=msg->trajectory[0].joint_trajectory.points[i].positions[0]/6.28*101*65536 ;
        ori_position[1]=msg->trajectory[0].joint_trajectory.points[i].positions[1]/6.28*101*65536 ;
        ori_position[2]=msg->trajectory[0].joint_trajectory.points[i].positions[2]/6.28*101*65536 ;
        ori_position[3]=msg->trajectory[0].joint_trajectory.points[i].positions[3]/6.28*101*65536 ;
        ori_position[4]=msg->trajectory[0].joint_trajectory.points[i].positions[4]/6.28*101*65536 ;
        ori_position[5]=msg->trajectory[0].joint_trajectory.points[i].positions[5]/6.28*101*65536 ;
        next_position[0]=msg->trajectory[0].joint_trajectory.points[i+1].positions[0]/6.28*101*65536 ;
        next_position[1]=msg->trajectory[0].joint_trajectory.points[i+1].positions[1]/6.28*101*65536 ;
        next_position[2]=msg->trajectory[0].joint_trajectory.points[i+1].positions[2]/6.28*101*65536 ;
        next_position[3]=msg->trajectory[0].joint_trajectory.points[i+1].positions[3]/6.28*101*65536 ;
        next_position[4]=msg->trajectory[0].joint_trajectory.points[i+1].positions[4]/6.28*101*65536 ;
        next_position[5]=msg->trajectory[0].joint_trajectory.points[i+1].positions[5]/6.28*101*65536 ;


        cn[0]=next_position[0]-ori_position[0];
        cn[1]=next_position[1]-ori_position[1];
        cn[2]=next_position[2]-ori_position[2];
        cn[3]=next_position[3]-ori_position[3];
        cn[4]=next_position[4]-ori_position[4];
        cn[5]=next_position[5]-ori_position[5];

        int round_i;

	int status =0;
        if (abs(cn[0])<1000&&abs(cn[1]<1000)&&abs(cn[2]<1000)&&abs(cn[3])<1000&&abs(cn[4]<1000)&&abs(cn[5]<1000)){
            round_i=20;
        }
        else if(abs(cn[0])<10000&&abs(cn[1]<10000)&&abs(cn[2]<10000)&&abs(cn[3])<10000&&abs(cn[4]<10000)&&abs(cn[5]<10000))
        {round_i=100/2;
	}

        else if(abs(cn[0])<50000&&abs(cn[1]<50000)&&abs(cn[2]<50000)&&abs(cn[3])<50000&&abs(cn[4]<50000)&&abs(cn[5]<50000))
        {round_i=200/4;

	}

        else if(abs(cn[0])<100000&&abs(cn[1]<100000)&&abs(cn[2]<100000)&&abs(cn[3])<100000&&abs(cn[4]<100000)&&abs(cn[5]<100000))
        //{round_i=300/3;
        {round_i=300/3;
		status=1;
        }

        else if(abs(cn[0])<500000&&abs(cn[1]<500000)&&abs(cn[2]<500000)&&abs(cn[3])<500000&&abs(cn[4]<500000)&&abs(cn[5]<500000))
        {round_i=500/2.5;
		status=1;
        }
        else if(abs(cn[0])<1000000&&abs(cn[1]<1000000)&&abs(cn[2]<1000000)&&abs(cn[3])<1000000&&abs(cn[4]<1000000)&&abs(cn[5]<1000000))
        {round_i=1000/4;
		status=1;
        }

        else {
        round_i=0;
        }


    //std::cout<<"round_i"<<round_i<<std::endl;




	                 uint32_t parameterlist2[10]={0};


        for (int i=0;i<round_i;i++) {
		int ss = 0;
		if (status==1&&10<i<round_i*0.7){i=i+10;}
		if (10<i<round_i*0.7){i=i;}
		//if (status==1&&i<round_i*0.7){i=i+10;}

                         if (cn[0]<0)
                         {
                             r1[i]=(ori_position[0]-i*abs(int(cn[0]/round_i)))*1;

                         }

                         else if(cn[0]>0)
                         {
                             r1[i]=(ori_position[0]+i*abs(int(cn[0]/round_i)))*1;

                         }

                         if (cn[1]<0)
                         {
                             r2[i]=ori_position[1]-i*abs(int(cn[1]/round_i));

                         }

                         else if(cn[1]>0)
                         {
                             r2[i]=ori_position[1]+i*abs(int(cn[1]/round_i));

                         }

                         if (cn[2]<0)
                         {
                             r3[i]=(ori_position[2]-i*abs(int(cn[2]/round_i)))*1;

                         }

                         else if(cn[2]>0)
                         {
                             r3[i]=(ori_position[2]+i*abs(int(cn[2]/round_i)))*1;

                         }








                         if (cn[3]<0)
                         {
                             r4[i]=ori_position[3]-i*abs(int(cn[3]/round_i));

                         }

                         else if(cn[3]>0)
                         {
                             r4[i]=ori_position[3]+i*abs(int(cn[3]/round_i));

                         }

                         if (cn[4]<0)
                         {
                             r5[i]=(ori_position[4]-i*abs(int(cn[4]/round_i)))*1;

                         }

                         else if(cn[4]>0)
                         {
                             r5[i]=(ori_position[4]+i*abs(int(cn[4]/round_i)))*1;

                         }

                         if (cn[5]<0)
                         {
                             r6[i]=ori_position[5]-i*abs(int(cn[5]/round_i));

                         }

                         else if(cn[5]>0)
                         {
                             r6[i]=ori_position[5]+i*abs(int(cn[5]/round_i));

                         }

			 //if(abs(cn[0])>1||abs(cn[1])>1||abs(cn[2])>1||abs(cn[3])>1||abs(cn[4])>1||abs(cn[5])>1)
			 //{
			//	 r1[i]=r1





                         parameterlist2[0] = -r1[i]+t1;
                         parameterlist2[1] = -r2[i]+t2;
                         parameterlist2[2] = -r3[i]+t3;
                         parameterlist2[3] = r4[i]+t4;
                         parameterlist2[4] = -r5[i]+t5;
                         parameterlist2[5] = r6[i]+t6;


        uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={30,30,30,30,30,30};
	sendCommand(6,canidlist2,cmd2,parameterlist2);
        if(1>0)
        {
            uint8_t buffer[1024];
            //读出数据
            //n = sp.read(buffer,48);

            for(int iiii=0; iiii<24; iiii++)
            {
                //16进制的方式打印到屏幕
                //std::cout << std::hex << (buffer[i] & 0xff) << " ";
            }
            //std::cout << std::endl;
            //把数据发送回去
            //sp.write(buffer, n);
        }

 }

	std::string bbuffer = sp.read(1024);

	bufferTransfor(bbuffer);//字符处理
}
}


int main(int argc, char** argv)
{
        ros::init(argc, argv, "client_node");
        ros::NodeHandle nh;
    //ros::Rate loop_rate(MESSAGE_FREQ); // set the rate as defined in the macro MESSAGE_FREQ
    ros::Rate loop_rate(500);
    ros::Rate loop_rate_slow(2);
        Listener listener;
        ros::Subscriber client_sub = nh.subscribe("/move_group/display_planned_path", 1000, &Listener::callback, &listener);



    //创建一个serial对象
    //创建timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyUSB0");
    //设置串口通信的波特率
    sp.setBaudrate(2000000);
    //串口设置timeout
    sp.setTimeout(to);
 
    try
    {
        //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
	for(int i=0;i<3;i++){    
	uint8_t canidlist[10]={0},cmd[10]={2};
	uint32_t parameterlist[10]={0};
        sendCommand(0,canidlist,cmd,parameterlist);  
        }
	for(int ii=0;ii<2;ii++){    
	uint8_t canidlist1[10]={0},cmd1[10]={4};
	uint32_t parameterlist1[10]={0};
        sendCommand(0,canidlist1,cmd1,parameterlist1);  
        }
	for(int iii=0;iii<1;iii++){    
	uint8_t canidlist6[10]={6},cmd6[10]={30};
	//uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={30,30,30,30,30,30};
	uint32_t parameterlist6[10]={t6};
        sendCommand(1,canidlist6,cmd6,parameterlist6);  
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	uint8_t canidlist5[10]={5},cmd5[10]={30};
	//uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={30,30,30,30,30,30};
	uint32_t parameterlist5[10]={t5};
        sendCommand(1,canidlist5,cmd5,parameterlist5);  
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();

	uint8_t canidlist4[10]={4},cmd4[10]={30};
	//uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={30,30,30,30,30,30};
	uint32_t parameterlist4[10]={t4};
        sendCommand(1,canidlist4,cmd4,parameterlist4);  
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();


	uint8_t canidlist3[10]={3},cmd3[10]={30};
	//uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={30,30,30,30,30,30};
	uint32_t parameterlist3[10]={t3};
        sendCommand(1,canidlist3,cmd3,parameterlist3);  
	loop_rate_slow.sleep();
	loop_rate_slow.sleep();
	uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={30,30,30,30,30,30};
	//uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={30,30,30,30,30,30};
	uint32_t parameterlist2[10]={t1,t2,t3,t4,t5,t6};
        sendCommand(6,canidlist2,cmd2,parameterlist2);  
        }
    
    while(ros::ok())
    {
        //获取缓冲区内的字节数
        //size_t n = sp.available();
	ros::spinOnce();
	loop_rate.sleep();
    }
    
    //关闭串口
    sp.close();
 
    return 0;
}
