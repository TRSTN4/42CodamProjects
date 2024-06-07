#ifndef DATA_H
#define DATA_H

class Data {
	private:
		int data;
	public:
		Data(int value);
		Data(const Data& src);
		Data& operator=(const Data& src);
		~Data();
		
		int getData() const;
};

#endif
