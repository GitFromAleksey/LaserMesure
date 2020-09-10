using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace HoningMachineConfig
{
    public partial class MainForm1 : Form
    {
        const Byte DEVICE_NUMBER = 1;
        private cProtocolSerializer m_ProtocolSerializer;
        private cProtocolDeSerializer m_ProtocolDeSerializer;
        Queue<byte> m_TxQueue;
        private int value_request_timer = 0;
        
        public MainForm1()
        {
            InitializeComponent();
            // разворачиваем форму на весь экран
            //this.WindowState = FormWindowState.Maximized;

            m_ProtocolSerializer = new cProtocolSerializer();
            m_ProtocolDeSerializer = new cProtocolDeSerializer(DEVICE_NUMBER);
            m_TxQueue = new Queue<byte>();
            //m_ProtocolDeSerializer.SetFunc(Logging);
            timer1.Enabled = true;
        }

        // вывод списка com портов
        private void portToolStripMenuItem_Click(object sender, EventArgs e)
        {
            toolStripComboBox1.Items.Clear();
            toolStripComboBox1.Items.AddRange(SerialPort.GetPortNames());
        }

        private void toolStripComboBox1_TextChanged(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
                return;
            serialPort1.PortName = toolStripComboBox1.Text;
            Logging("Selected new port name: " + toolStripComboBox1.Text);
        }

        private void openPortToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                Logging("serialPort1.IsOpen");
            }

            try
            {
                serialPort1.Open();
                toolStripComboBox1.Enabled = false;
            }
            catch (Exception ex)
            {
                Logging("serialPort1.Open() error: " + ex.Message);
            }
            finally
            {
                Logging("serialPort1.Open() sucsess");
            }
        }

        private void closePortToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                toolStripComboBox1.Enabled = true;
                Logging("serialPort1.Close()");
            }
        }

        private async void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int bytesToRead = serialPort1.BytesToRead;
            int bytesCnt = 0;
            int[] buf = new int[bytesToRead];
            string str = "";
            TextBox tb = textBoxLog;

            while (bytesCnt < bytesToRead)
            {
                buf[bytesCnt++] = serialPort1.ReadByte();
            }

            m_ProtocolDeSerializer.AddBytes(buf);

            bytesCnt = 0;
            string hex_string = "";
            while (bytesCnt < bytesToRead)
            {
            	char ch = (buf[bytesCnt] == 0) ? ('0') : ((char)buf[bytesCnt]);
            	hex_string += buf[bytesCnt].ToString() + ',';
            	str += ch;
            	bytesCnt++;
            }

            str +="\r\n";
            //str = m_ProtocolDeSerializer.ToString();
            this.textBoxLog.BeginInvoke((MethodInvoker)(() => this.textBoxLog.Text += str + hex_string));
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
        	if(++value_request_timer > 15)
        	{
        		value_request_timer = 0;
        		SendData(m_ProtocolSerializer.KeyRead());
        	}
        	if(value_request_timer == 5)
        		SendData(m_ProtocolSerializer.KeyReadDisplayValue());
        	
        	if(m_TxQueue.Count > 0)
        	{
	        	if(serialPort1.IsOpen)
	        	{
	        		byte[] data = new byte[m_TxQueue.Count];
	        		int i = 0;
	        		while(m_TxQueue.Count > 0)
	        		{
	        			data[i++] = m_TxQueue.Dequeue();
	        		}
	        		serialPort1.Write(data, 0, data.Length);
	        	}
        	}
        	
			labelValue.Text = m_ProtocolDeSerializer.GetValueString();
        }

        private void textBoxToSend_KeyDown(object sender, KeyEventArgs e)
        {
            if (!serialPort1.IsOpen)
                return;
            serialPort1.Write(textBoxToSend.Text);
        }

        private void test_button_Click(object sender, EventArgs e)
        {
        	byte[] data = new byte[7];
        	int i = 0;
			int j = 0;
			
        	data[i++] = (byte)textBoxToSend.Text[j++];
        	data[i++] = (byte)textBoxToSend.Text[j++];
        	data[i++] = (byte)textBoxToSend.Text[j++];
        	data[i++] = (byte)textBoxToSend.Text[j++];
        	data[i++] = (byte)textBoxToSend.Text[j++];
        	data[i++] = (byte)textBoxToSend.Text[j++];
        	data[i++] = (byte)textBoxToSend.Text[j++];
        	
        	SendData(data);

        }

        private void buttonsMachineDriving_Click(object sender, EventArgs e)
        {
        	byte[] data = new byte[7];
        	int i = 0;

        	
            if (sender == buttonReadCurrentRecord)
            {
            	SendData(m_ProtocolSerializer.KeyReadDisplayValue());
            }
            
			if (sender == buttonSave)
			{
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonRead)
			{ 
	        	SendData(m_ProtocolSerializer.KeyRead());
	        	SendData(m_ProtocolSerializer.KeyRead());
			}
			if (sender == buttonPlus)
			{ 
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'2';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonMenu)
			{ 
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'3';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonMinus)
			{
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'4';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonArea)
			{
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'5';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonLevelBubble)
			{
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'6';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonPythegoras)
			{
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'7';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonTimer)
			{
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'8';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
			if (sender == buttonClearOff)
			{
				data[i++] = (Byte)'A';
	        	data[i++] = (Byte)'T';
	        	data[i++] = (Byte)'K';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'0';
	        	data[i++] = (Byte)'9';
	        	data[i++] = (Byte)'#';
	        	SendData(data);
			}
        }

        private void SendData(byte[] data)
        {
//            if(serialPort1.IsOpen)
//                serialPort1.Write(data, 0, data.Length);
            
            foreach(byte b in data)
            	m_TxQueue.Enqueue(b);
        }

        private void Logging(string text)
        {
            textBoxLog.Text += text + "\r\n";
        }

        private void MainForm1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Delete)
            {
                textBoxLog.Clear();
            }
            if (e.KeyValue == 85) // U
            {
            }
            if (e.KeyValue == 68) // D
            {
            }
            if (e.KeyValue == 83) // S
            {
            }
        }


    }
}
