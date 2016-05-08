//////////////////////////////////////////////////////////////////////////////
//
//	BHMorse.h - Library for Morse code
//
//	Copyright © 2016 Robert L. Bailey
//
//	Send Morse Code, including generating random characters, groups of
//	characters, or plausible QSOs.
//
//////////////////////////////////////////////////////////////////////////////
//
//	This file is part of BHMorse.
//
//	BHMorse is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	BHMorse is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with BHMorse.  If not, see <http://www.gnu.org/licenses/>.
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

typedef uint8_t BH_pin_t;

// EEPROM safety signature

#define BHMORSE_EEPROM_SIGNATURE_V1 0x5AFE	// safe

// EEPROM memory map

#define BHMORSE_EEPROM_ADDR_SIGNATURE 0

#define BHMORSE_EEPROM_ADDR_OVERALLSPEED \
	(BHMORSE_EEPROM_ADDR_SIGNATURE + \
	sizeof(BHMorse::eepromSignature_t))

#define BHMORSE_EEPROM_ADDR_USERCHARSPEED \
	(BHMORSE_EEPROM_ADDR_OVERALLSPEED + \
	sizeof(BHMorse::wpm_t))

#define BHMORSE_EEPROM_ADDR_HIGHESTENABLEDDIFFICULTY \
	(BHMORSE_EEPROM_ADDR_USERCHARSPEED + \
	sizeof(BHMorse::wpm_t))

#define BHMORSE_EEPROM_ADDR_PITCH \
	(BHMORSE_EEPROM_ADDR_HIGHESTENABLEDDIFFICULTY + \
	sizeof(BHMorse::difficulty_t))

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

// valid real character (i.e., not including specials) difficulty range

#define BHMORSE_MIN_CHARACTER_DIFFICULTY 1
#define BHMORSE_MAX_CHARACTER_DIFFICULTY 7

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
#define BHMORSE_DEFAULT_ENABLEDDIFFICULTY 4
#define BHMORSE_DEFAULT_PITCH 1000
#define BHMORSE_DEFAULT_RUNMODE Idle

// character element map helpers


#define BHMORSE_CHAR_ELEMENT_MAP_OFFSET ' '
#define BHMORSE_CHAR_ELEMENT_MAP_DIFFICULTY_SPACE 8
#define BHMORSE_CHAR_ELEMENT_MAP_DIFFICULTY_UNUSED 9
#define BHMORSE_CHAR_ELEMENT_MAP_HIELEMENTBIT 31
#define BHMORSE_CHAR_ELEMENT_MAP_UNUSED {BHMORSE_CHAR_ELEMENT_MAP_DIFFICULTY_UNUSED, 0, 0}

// message

#define BHMORSE_MESSAGE_MAXLEN 250
#define BHMORSE_MESSAGE_BUFRSIZE (BHMORSE_MESSAGE_MAXLEN + 1)

// classes

class BHMorse
{
public:

	// typedefs

	typedef unsigned long eepromSignature_t;
	typedef unsigned long wpmFactor_t;
	typedef unsigned long duration_t;
	typedef byte wpm_t;
	typedef unsigned int hz_t;
	typedef byte difficulty_t;
	typedef byte charElemMap_numElems_t;
	typedef unsigned long charElemMap_elements_t;

	typedef struct
	{
		char d[BHMORSE_FIRSTNAME_MAXLEN];
	} firstName_t;

	typedef struct
	{
		char d[BHMORSE_CITY_MAXLEN];
	} city_t;

	typedef struct
	{
		char d[BHMORSE_QSOPART_MAXLEN];
	} qsoPart_t;
	
	// a character map element

	struct charElement_t
	{
		difficulty_t difficulty;
		charElemMap_numElems_t numElems;
		charElemMap_elements_t elements;
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

	// QSO parts

	enum QSOPart_Row
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
	
private:

	//////////////////////////////////////////////////////////////////////////////
	//
	// Stuff available for random senders
	//
	//////////////////////////////////////////////////////////////////////////////

	static const firstName_t _firstNames[];
	static const city_t _cities[];
	static const qsoPart_t _QSOParts[];

	//////////////////////////////////////////////////////////////////////////////
	//
	// Properties
	//
	//////////////////////////////////////////////////////////////////////////////

	//------------------------------------------------------------
	// Morse parameters
	//------------------------------------------------------------

	// WPM calculation scheme factor, in (ms * words) / (dit * minute)

	wpmFactor_t _wpmSchemeFactor;

	// overall speed; "s" in ARRL calculations

	wpm_t _overallSpeed;

	// user-selected character speed

	wpm_t _userCharSpeed;

	// highest character difficulty for random sending

	difficulty_t _enabledDifficulty;

	//------------------------------------------------------------
	// sound parameters
	//------------------------------------------------------------

	// tone() pin number

	BH_pin_t _tonePin;

	// tone pitch

	hz_t _pitch;

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

	// map of characters no harder than enabled difficulty

	static const charElement_t _charElemMap[];
	byte* _ptrsToCharsWithEnabledDifficulty;
	byte _numCharDifficultyPtrs;
	
	// copy of the character currently being sent

	charElement_t _tempChar;

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
	eepromSignature_t readSignature();
	void readOverallSpeed();
	void readUserCharSpeed();
	void readEnabledDifficulty();
	void readPitch();

	void saveSignature();
	void saveOverallSpeed();
	void saveUserCharSpeed();
	void saveEnabledDifficulty();
	void savePitch();
	
	void redoCharDifficultyPtrs();

	charElement_t getCharElement(int p);
	void getQSOPart(char* retV, int p);
	boolean isSpace(charElement_t pChar);
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

	wpmFactor_t wpmSchemeFactor();
	wpm_t overallSpeed();
	wpm_t userCharSpeed();
	difficulty_t enabledDifficulty();

	// computed

	wpm_t charSpeed();
	duration_t charDitMarkTime();
	duration_t charDitSpaceTime();
	duration_t charDahMarkTime();
	duration_t farnsworthDelayTime();
	duration_t interCharSpaceTime();
	duration_t interWordSpaceTime();

	//------------------------------------------------------------
	// Morse parameter setters
	//------------------------------------------------------------

	void setWpmSchemeFactor(wpmFactor_t newValue);
	void setOverallSpeed(wpm_t newValue);
	void setUserCharSpeed(wpm_t newValue);
	void setEnabledDifficulty(difficulty_t newValue);

	//------------------------------------------------------------
	// sound parameter getters
	//------------------------------------------------------------

	BH_pin_t tonePin();
	hz_t pitch();

	//------------------------------------------------------------
	// sound parameter setters
	//------------------------------------------------------------

	void setTonePin(BH_pin_t newValue);
	void setPitch(hz_t newValue, bool pSave);

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

	void begin(BH_pin_t tonePin);
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
