#include "SDModule.h"

SDModule::SDModule(int port) : m_port(port)
{ }

SDModule::~SDModule()
{ }

SDModule::SDModule(const SDModule & copy) : m_port(copy.m_port)
{ } 

int SDModule::setup()
{
	int retval = 1;
	
	if(!SD.begin(m_port))
		retval = 0;
	
	return retval;
}

int SDModule::write(String data,int year, int month)
{
	String fileName;	// We break up the files by the datas year and month
	
	fileName += String(month);
	fileName += '_';
	fileName += String(year);
	fileName += ".TXT";
	
	int retval = 0;		//return value 0 is fail 1 is success
	int newFile = 0; 	//is this a new file?
	
	if(!SD.exists(fileName))
		newFile = 1;	//yes!
	
	File myFile = SD.open(fileName,FILE_WRITE);	//If file dosnt exist it will create
	if(myFile);
	{
		if(newFile)
			myFile.println("Date Time,Internal temp(C),External temp(C) ,Humidity(%),Weight(g)");	//add this top header if its a new file
		
		myFile.println(data);
		myFile.close();	//close to save
		retval = 1;
	}
	
	return retval;
}

void SDModule::readToBluetooth()
{
	String fileType = ".TXT";
	File root = SD.open("/");	//Open the SD card directory
	
	while(true)
	{
		File entry = root.openNextFile();	// Open the first file in the directory
		
		if(!entry)	// if there are no files left we are done
		{
			break;
		}	
		
		String temp = entry.name();	// get the name

    
		if(temp.endsWith(fileType))	// if the file ends with .TXT then we can read it to bluetooth
		{
			while(entry.available())		// read the whole file
				Serial1.write(entry.read());
			
		}
	}
}
