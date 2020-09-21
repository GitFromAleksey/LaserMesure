#ifndef SW_T4S_PROTOCOL_BUILDER_H
#define SW_T4S_PROTOCOL_BUILDER_H

class cSwT4sProtocolBuilder
{
	public:
		cSwT4sProtocolBuilder();
		~cSwT4sProtocolBuilder();

    int KeyRead(char* buf, int bufSize);
    int KeyReadDisplayValue(char* buf, int bufSize);

	private:
    
    int ProtocolSerealize(char* buf, int bufSize, char* keyCode);
  
};


#endif /* SW_T4S_PROTOCOL_BUILDER_H */
