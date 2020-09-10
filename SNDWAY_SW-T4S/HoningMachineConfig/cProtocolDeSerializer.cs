using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HoningMachineConfig
{

    class cProtocolDeSerializer
    {
		uint value;
    	
        public cProtocolDeSerializer(Byte deviceNumber)
        {
        	value = 0;
        }

        public void AddBytes(int[] data)
        {
			if(data.Length > 7)
			{
				string tmp = "";
				byte b = (byte)data[0];
				tmp += (char)b;
				b = (byte)data[1];
				tmp += (char)b;
				b = (byte)data[2];
				tmp += (char)b;
				
				if(tmp == "ATD")
				{
					value = 0;
					value = ((uint)data[3]<<24) | ((uint)data[4]<<16) | ((uint)data[5]<<8) | (uint)data[6];
				}
			}
        }

        public string GetValueString()
        {
        	float tmp = ((float)value)/10000;
        	string res = tmp.ToString();
        	return res;
        }
        
        public string ToString()
        {
            string res = "";
            
            return res;
        }

    }
}
