using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HoningMachineConfig
{
    
	
	struct RequestProtocol
    {
        public Byte DeviceNumber;
        public Byte CMD;
        public UInt16 RegisterNumber;
        public UInt16 RegistersToRead;
        public UInt32 DataToWrite;
        public Byte CRC8;
    }
    
    enum ProtocolCommands
    {
        CMD_READ_RO_REG = 3,
        CMD_WRITE_RW_REG = 4,
        CMD_READ_RW_REG = 5,

        PROTOCOL_CMD_MACHINE_PWR_ON = 6,
        PROTOCOL_CMD_MACHINE_PWR_OFF = 7,
        PROTOCOL_CMD_TOOL_LIFT_UP = 8,
        PROTOCOL_CMD_TOOL_LIFT_DOWN = 9,
        PROTOCOL_CMD_TOOL_LIFT_STOP = 10,
        PROTOCOL_CMD_TOOL_ROTATE_RUN = 11,
        PROTOCOL_CMD_TOOL_ROTATE_STOP = 12,
        PROTOCOL_CMD_TOOL_STOP = 13,
        PROTOCOL_CMD_VERTICAL_FEED_MOTOR_ON = 14,
        PROTOCOL_CMD_VERTICAL_FEED_MOTOR_OFF = 15,
        	
		PROTOCOL_CMD_PRESS_KEY_1 = 16,
		PROTOCOL_CMD_PRESS_KEY_2 = 17,
		PROTOCOL_CMD_PRESS_KEY_3 = 18,
		PROTOCOL_CMD_PRESS_KEY_4 = 19,
		PROTOCOL_CMD_PRESS_KEY_5 = 20,
		PROTOCOL_CMD_PRESS_KEY_6 = 21,
		PROTOCOL_CMD_PRESS_KEY_7 = 22,
		PROTOCOL_CMD_PRESS_KEY_8 = 23,
		PROTOCOL_CMD_PRESS_KEY_9 = 24,
		PROTOCOL_CMD_SWITCH_TOGGLE = 25
    }

    class cProtocolSerializer
    {
        const Byte SIGN_BEGIN_PACKET = (Byte)'<';
        const Byte SIGN_END_PACKET = (Byte)'>';
        
        const string PACKET_BEGIN_SEQUENSE = "AT";
        const char PACKET_END_SYMBOL = '#';
        
        const char PACKET_KEY_PRESS_IMITATION_SYMBOL = 'K';
        
        const string PACKET_KEY_CODE_READ = "001";
        const string PACKET_KEY_CODE_PLUS = "002";
        const string PACKET_KEY_CODE_MENU = "003";
        const string PACKET_KEY_CODE_MINUS = "004";
        const string PACKET_KEY_CODE_AREA = "005";
        const string PACKET_KEY_CODE_LEVEL_BUBBLE = "006";
        const string PACKET_KEY_CODE_PYPHAGORAS = "007";
        const string PACKET_KEY_CODE_TIMER = "008";
        const string PACKET_KEY_CODE_CLEAR_OFF = "009";
        const string PACKET_KEY_CODE_SAVE = "00A";
        const string PACKET_KEY_CODE_READ_DISPLEY_VALUE = "00C";
        
        

        
        public cProtocolSerializer()
        {
        }

        public byte[] KeyRead()
        {
        	return SerealizeProtocol(PACKET_KEY_CODE_READ);
        }

        public byte[] KeyReadDisplayValue()
        {
        	return SerealizeProtocol(PACKET_KEY_CODE_READ_DISPLEY_VALUE);
        }        
        
        private byte[] SerealizeProtocol(string keyCode)
        {
            Byte[] b = new Byte[7];
            int cnt = 0;

            b[cnt++] = (byte)PACKET_BEGIN_SEQUENSE[0];
			b[cnt++] = (byte)PACKET_BEGIN_SEQUENSE[1];

			b[cnt++] = (byte)PACKET_KEY_PRESS_IMITATION_SYMBOL;
			
			b[cnt++] = (byte)keyCode[0];
			b[cnt++] = (byte)keyCode[1];
			b[cnt++] = (byte)keyCode[2];
			
			b[cnt++] = (byte)PACKET_END_SYMBOL;

            return b;
        }
    }
}
