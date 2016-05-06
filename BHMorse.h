//////////////////////////////////////////////////////////////////////////////
//
//	BHMorse.h - Library for Morse code
//
//	Created 2016-04-01 by Rob Bailey, WM8S
//
////////////////////////////////////////////////////////////////////////////////

#ifndef BHMorse_h
#define BHMorse_h

#include <Arduino.h>

//#undef BHMORSE_DEBUG
#define BHMORSE_DEBUG

// misc stuff

#define BH_ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define BH_END_OF_STRING '\0'

typedef uint8_t BH_PIN;

// EEPROM safety signature

#define BHMORSE_EEPROM_SIGNATURE_V1 0x5AFE	// safe

// EEPROM memory map

#define BHMORSE_EEPROM_ADDR_SIGNATURE 0

#define BHMORSE_EEPROM_ADDR_OVERALLSPEED \
	(BHMORSE_EEPROM_ADDR_SIGNATURE + \
	sizeof(BHMorse_EEPROMSignature))

#define BHMORSE_EEPROM_ADDR_USERCHARSPEED \
	(BHMORSE_EEPROM_ADDR_OVERALLSPEED + \
	sizeof(BHMorse_WpmFactor))

#define BHMORSE_EEPROM_ADDR_HIGHESTENABLEDGROUP \
	(BHMORSE_EEPROM_ADDR_USERCHARSPEED + \
	sizeof(BHMorse_WpmFactor))

#define BHMORSE_EEPROM_ADDR_PITCH \
	(BHMORSE_EEPROM_ADDR_HIGHESTENABLEDGROUP + \
	sizeof(BHMorse_charElemMap_Group))

// EEPROM write delay

#define BHMORSE_EEPROM_WRITE_DELAY 50

// for random tables

#define BHMORSE_FIRSTNAME_MAXLEN 10

#define BHMORSE_CITY_MAXLEN 20

#define BHMORSE_QSOPART_MAXLEN 20

#define BHMORSE_PREFIX_MIN 'A'
#define BHMORSE_PREFIX_MAX 'Z'

#define BHMORSE_NUMBER_MIN '0'
#define BHMORSE_NUMBER_MAX '9'

#define BHMORSE_SUFFIX_MIN 'A'
#define BHMORSE_SUFFIX_MAX 'Z'

#define BHMORSE_RST_R_MIN '3'
#define BHMORSE_RST_R_MAX '5'

#define BHMORSE_RST_S_MIN '4'
#define BHMORSE_RST_S_MAX '9'

#define BHMORSE_RST_T_MIN '7'
#define BHMORSE_RST_T_MAX '9'

// for randomSeed()

#define BHMORSE_UNUSED_ANALOGPIN 0

// group length range

#define BHMORSE_RANDOMGROUP_MIN 3
#define BHMORSE_RANDOMGROUP_MAX 7

// weights

#define BHMORSE_DITS_PER_DAH 3
#define BHMORSE_DITS_PER_CHARSPACE 7

// valid WPM range

#define BHMORSE_MIN_WPM 5
#define BHMORSE_MAX_WPM 60

// valid real character (i.e., not including specials) group range

#define BHMORSE_MIN_CHARACTER_GROUP 1
#define BHMORSE_MAX_CHARACTER_GROUP 7

// valid pitch range

#define BHMORSE_MIN_PITCH 400
#define BHMORSE_MAX_PITCH 2000

// WPM scheme factors

#define BHMORSE_WPMSCHEMEFACTOR_PARIS 1200
#define BHMORSE_WPMSCHEMEFACTOR_CODEX 1000

// max speed that Farnsworth is allowed

#define BHMORSE_FARNSWORTH_CAP 18

// setting defaults

#define BHMORSE_DEFAULT_WPMSCHEMEFACTOR BHMORSE_WPMSCHEMEFACTOR_PARIS
#define BHMORSE_DEFAULT_OVERALLSPEED 13
#define BHMORSE_DEFAULT_USERCHARSPEED 18
#define BHMORSE_DEFAULT_HIGHESTENABLEDGROUP 4
#define BHMORSE_DEFAULT_PITCH 1000
#define BHMORSE_DEFAULT_RUNMODE Idle

// character element map helpers


#define BHMORSE_CHAR_ELEMENT_MAP_OFFSET ' '
#define BHMORSE_CHAR_ELEMENT_MAP_GROUP_SPACE 8
#define BHMORSE_CHAR_ELEMENT_MAP_GROUP_UNUSED 9
#define BHMORSE_CHAR_ELEMENT_MAP_HIELEMENTBIT 31
#define BHMORSE_CHAR_ELEMENT_MAP_UNUSED {BHMORSE_CHAR_ELEMENT_MAP_GROUP_UNUSED, 0, 0}

// message

#define BHMORSE_MESSAGE_MAXLEN 250
#define BHMORSE_MESSAGE_BUFRSIZE (BHMORSE_MESSAGE_MAXLEN + 1)

// enums

enum BHMorse_QSOPart_Row
{
	FB1 = 0,
	FB2,
	FB3,
	FB4,
	FB5,
	DE,
	RST1,
	RST2,
	Name1,
	Name2,
	Name3,
	Name4,
	QTH1,
	QTH2,
	Bk2U1,
	Bk2U2,
	Bk2U3,
	K1,
	K2
};

// typedefs

typedef	unsigned long BHMorse_EEPROMSignature;
typedef	unsigned long BHMorse_WpmFactor;
typedef	unsigned long BHMorse_Duration;
typedef byte BHMorse_Wpm;
typedef unsigned int BHMorse_Hz;
typedef byte BHMorse_charElemMap_Group;
typedef byte BHMorse_charElemMap_NumElems;
typedef unsigned long BHMorse_charElemMap_Elements;

typedef struct
{
	char d[BHMORSE_FIRSTNAME_MAXLEN];
} BHMorse_FirstName;

typedef struct
{
	char d[BHMORSE_CITY_MAXLEN];
} BHMorse_City;

typedef struct
{
	char d[BHMORSE_QSOPART_MAXLEN];
} BHMorse_QSOPart;

// classes

class BHMorse
{
public:

	// a character map element

	struct charElement
	{
		BHMorse_charElemMap_Group charGroup;
		BHMorse_charElemMap_NumElems numElems;
		BHMorse_charElemMap_Elements elements;
	};
	
	// run modes

	enum RunMode
	{
		Idle = 0,
		SendMessage,
		SendChars,
		SendGroups,
		SendQSOs,
		SendFile
	};
	
private:

	//////////////////////////////////////////////////////////////////////////////
	//
	// Stuff available for random senders
	//
	//////////////////////////////////////////////////////////////////////////////

	static const BHMorse_FirstName _firstNames[];
	static const BHMorse_City _cities[];
	static const BHMorse_QSOPart _QSOParts[];

	//////////////////////////////////////////////////////////////////////////////
	//
	// Properties
	//
	//////////////////////////////////////////////////////////////////////////////

	//------------------------------------------------------------
	// Morse parameters
	//------------------------------------------------------------

	// WPM calculation scheme factor, in (ms * words) / (dit * minute)

	BHMorse_WpmFactor _wpmSchemeFactor;

	// overall speed; "s" in ARRL calculations

	BHMorse_Wpm _overallSpeed;

	// user-selected character speed

	BHMorse_Wpm _userCharSpeed;

	// highest enabled character group for random sending

	BHMorse_charElemMap_Group _highestEnabledGroup;

	//------------------------------------------------------------
	// sound parameters
	//------------------------------------------------------------

	// tone() pin number

	BH_PIN _tonePin;

	// tone pitch

	BHMorse_Hz _pitch;

	//------------------------------------------------------------
	// message parameters
	//------------------------------------------------------------

	// the message to send

	char _message[BHMORSE_MESSAGE_BUFRSIZE];

	//------------------------------------------------------------
	// run mode
	//------------------------------------------------------------

	RunMode _runMode;

	//------------------------------------------------------------
	// internal stuff
	//------------------------------------------------------------

	// internal buffer for building a message

	char _tmpBuffer[BHMORSE_MESSAGE_BUFRSIZE];

	// map of characters within current group range

	static const charElement _charElemMap[];
	byte* _ptrsToCharsInGroupRange;
	byte _numCharGroupPtrs;
	
	// copy of the character currently being sent

	charElement _tempChar;

	// the number of elements within the current character already sent

	int _numElemsInCharSent;

	// the number of characters within the message already sent

	int _numCharsInMsgSent;

	//////////////////////////////////////////////////////////////////////////////
	//
	// Procedures
	//
	//////////////////////////////////////////////////////////////////////////////

	// other

	void loadSettings();
	BHMorse_EEPROMSignature readSignature();
	void readOverallSpeed();
	void readUserCharSpeed();
	void readHighestEnabledGroup();
	void readPitch();

	void saveSignature();
	void saveOverallSpeed();
	void saveUserCharSpeed();
	void saveHighestEnabledGroup();
	void savePitch();
	
	void redoCharGroupPtrs();

	charElement getCharElement(int p);
	void getQSOPart(char* retV, int p);
	boolean isSpace(charElement pChar);
	void loadChar();
	void loadNextChar();
	void loadNextGroup();
	void loadNextQSO();


public:

	//////////////////////////////////////////////////////////////////////////////
	//
	// Properties
	//
	//////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////
	//
	// Procedures
	//
	//////////////////////////////////////////////////////////////////////////////

	//------------------------------------------------------------
	// constructors
	//------------------------------------------------------------

	BHMorse();

	//------------------------------------------------------------
	// Morse parameter getters
	//------------------------------------------------------------

	// backed

	BHMorse_WpmFactor wpmSchemeFactor();
	BHMorse_Wpm overallSpeed();
	BHMorse_Wpm userCharSpeed();
	BHMorse_charElemMap_Group highestEnabledGroup();

	// computed

	BHMorse_Wpm charSpeed();
	BHMorse_Duration charDitMarkTime();
	BHMorse_Duration charDitSpaceTime();
	BHMorse_Duration charDahMarkTime();
	BHMorse_Duration farnsworthDelayTime();
	BHMorse_Duration interCharSpaceTime();
	BHMorse_Duration interWordSpaceTime();

	//------------------------------------------------------------
	// Morse parameter setters
	//------------------------------------------------------------

	void setWpmSchemeFactor(BHMorse_WpmFactor newValue);
	void setOverallSpeed(BHMorse_Wpm newValue);
	void setUserCharSpeed(BHMorse_Wpm newValue);
	void setHighestEnabledGroup(BHMorse_charElemMap_Group newValue);

	//------------------------------------------------------------
	// sound parameter getters
	//------------------------------------------------------------

	BH_PIN tonePin();
	BHMorse_Hz pitch();

	//------------------------------------------------------------
	// sound parameter setters
	//------------------------------------------------------------

	void setTonePin(BH_PIN newValue);
	void setPitch(BHMorse_Hz newValue, bool pSave);

	//------------------------------------------------------------
	// message parameter getters
	//------------------------------------------------------------

	void message(char* retV);

	//------------------------------------------------------------
	// message parameter setters
	//------------------------------------------------------------

	void setMessage(char const* newValue);

	//------------------------------------------------------------
	// other getters
	//------------------------------------------------------------

	RunMode	runMode();

	//------------------------------------------------------------
	// other setters
	//------------------------------------------------------------

	void setRunMode(RunMode newValue);

	//------------------------------------------------------------
	// misc. methods
	//------------------------------------------------------------

	void begin(BH_PIN tonePin);
	void resetSettings();

	boolean elemsRemainInChar();
	boolean charsRemainInMsg();
	boolean msgDone();

	void sendMessage(const char* pMessage);
	void sendUntilMsgDone();
	void sendNextElem();
	void sendMark(bool pStopAfter);
	void sendSpace();

	void waitInterElemSpace();
	void waitInterCharSpace();
	void waitInterWordSpace();

	void getRandomName(char* retV);
	void getRandomCity(char* retV);
	void getRandomCall(char* retV);
	void getRandomRST(char* retV);
};

#endif
