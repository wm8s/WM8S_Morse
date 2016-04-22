//////////////////////////////////////////////////////////////////////////////
//
//	BHMorse.cpp - Library for Morse code
//
//	Created 2016-04-01 by Rob Bailey, WM8S
//
//
//
//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <EEPROM.h>
#include "BHMorse.h"

//////////////////////////////////////////////////////////////////////////////
// Stuff available for random senders
//////////////////////////////////////////////////////////////////////////////

// names

const BHMorse_FirstName BHMorse::_firstNames[BHMORSE_FIRSTNAME_NUMROW] PROGMEM =
{
	{ "AARAV" },
	{ "AGUSTIN" },
	{ "AI" },
	{ "ALEX" },
	{ "ALEXANDER" },
	{ "AMANDA" },
	{ "AMY" },
	{ "ANDREAS" },
	{ "ANDREI" },
	{ "ANDY" },
	{ "ANGELA" },
	{ "ANNA" },
	{ "ANTONIO" },
	{ "ARON" },
	{ "ASHLEY" },
	{ "AYA" },
	{ "AZIZ" },
	{ "BARBARA" },
	{ "BEN" },
	{ "BETTY" },
	{ "BILL" },
	{ "BRANDON" },
	{ "BRENDA" },
	{ "BRIAN" },
	{ "CAROL" },
	{ "CAROLYN" },
	{ "CATHY" },
	{ "CHARLES" },
	{ "CHRIS" },
	{ "CHRISTINE" },
	{ "CYNTHIA" },
	{ "DANIEL" },
	{ "DAVID" },
	{ "DEBORAH" },
	{ "DEBRA" },
	{ "DENNIS" },
	{ "DIEGO" },
	{ "DONALD" },
	{ "DONNA" },
	{ "DOROTHY" },
	{ "ED" },
	{ "ELIAS" },
	{ "EMILY" },
	{ "ERIC" },
	{ "FILIP" },
	{ "FRANCESCO" },
	{ "FRANK" },
	{ "FREJA" },
	{ "GARY" },
	{ "GEORGE" },
	{ "GEORGI" },
	{ "GREG" },
	{ "HANS" },
	{ "HAO" },
	{ "HEATHER" },
	{ "HELEN" },
	{ "HIROTO" },
	{ "HUGO" },
	{ "IOANNIS" },
	{ "JACK" },
	{ "JACOB" },
	{ "JANET" },
	{ "JASON" },
	{ "JAYDEN" },
	{ "JEFF" },
	{ "JENNIFER" },
	{ "JERRY" },
	{ "JESSICA" },
	{ "JIE" },
	{ "JIM" },
	{ "JOAO" },
	{ "JOE" },
	{ "JOHN" },
	{ "JONAS" },
	{ "JOSE" },
	{ "JOSHUA" },
	{ "JUAN" },
	{ "JUSTIN" },
	{ "KAREN" },
	{ "KEN" },
	{ "KEVIN" },
	{ "KIM" },
	{ "LARA" },
	{ "LARRY" },
	{ "LAURA" },
	{ "LINDA" },
	{ "LISA" },
	{ "LIZ" },
	{ "LUCIA" },
	{ "LUIS" },
	{ "MAIA" },
	{ "MALIK" },
	{ "MARGARET" },
	{ "MARIA" },
	{ "MARK" },
	{ "MARY" },
	{ "MASON" },
	{ "MATT" },
	{ "MAXIM" },
	{ "MAYA" },
	{ "MEHMET" },
	{ "MICHELLE" },
	{ "MIGUEL" },
	{ "MIKE" },
	{ "MIN JOON" },
	{ "MISSY" },
	{ "NANCY" },
	{ "NICK" },
	{ "NICOLAS" },
	{ "NICOLE" },
	{ "NOAM" },
	{ "OMAR" },
	{ "PABLO" },
	{ "PAMELA" },
	{ "PATRICK" },
	{ "PAUL" },
	{ "PEDRO" },
	{ "QIAN" },
	{ "RACHEL" },
	{ "RAYMOND" },
	{ "REBECCA" },
	{ "RENZ" },
	{ "RICH" },
	{ "RIKO" },
	{ "ROB" },
	{ "RON" },
	{ "RUTH" },
	{ "RYAN" },
	{ "SAKURA" },
	{ "SAM" },
	{ "SANDY" },
	{ "SANTIAGO" },
	{ "SARAH" },
	{ "SCOTT" },
	{ "SEBASTIAN" },
	{ "SHARON" },
	{ "SHIRLEY" },
	{ "SHU" },
	{ "SOMCHAI" },
	{ "SOMSAK" },
	{ "SOPHIA" },
	{ "STEPH" },
	{ "STEPHEN" },
	{ "STEVE" },
	{ "SUE" },
	{ "TAMAR" },
	{ "TIM" },
	{ "TOM" },
	{ "TOMAS" },
	{ "TONY" },
	{ "VIRGINIA" },
	{ "WEI" },
	{ "XIAN" },
	{ "YUSUF" },
	{ "YUVAL" }
};

// cities

const BHMorse_City BHMorse::_cities[BHMORSE_CITY_NUMROW] PROGMEM =
{
	{ "AHMEDABAD INDIA" },
	{ "ALBUQUERQUE NM" },
	{ "ANAHEIM CA" },
	{ "ANCHORAGE AK" },
	{ "ANKARA TURKEY" },
	{ "ATLANTA GA" },
	{ "AURORA CO" },
	{ "AUSTIN TX" },
	{ "BAKERSFIELD CA" },
	{ "BALTIMORE MD" },
	{ "BANGALORE INDIA" },
	{ "BANGKOK THAILAND" },
	{ "BARCELONA SPAIN" },
	{ "BATON ROUGE LA" },
	{ "BEIJING CHINA" },
	{ "BELO HORIZONTE BR" },
	{ "BERLIN GERMANY" },
	{ "BIRMINGHAM AL" },
	{ "BOGOTA COLOMBIA" },
	{ "BOISE ID" },
	{ "BOSTON MA" },
	{ "BUFFALO NY" },
	{ "CHANDLER AZ" },
	{ "CHARLESTON WV" },
	{ "CHARLOTTE NC" },
	{ "CHENGDU CHINA" },
	{ "CHENNAI INDIA" },
	{ "CHEYENNE WY" },
	{ "CHICAGO IL" },
	{ "CHONGQING CHINA" },
	{ "CHULA VISTA CA" },
	{ "CINCINNATI OH" },
	{ "CLEVELAND OH" },
	{ "COLORADO SPRINGS CO" },
	{ "COLUMBUS OH" },
	{ "CORPUS CHRISTI TX" },
	{ "DALLAS TX" },
	{ "DENVER CO" },
	{ "DETROIT MI" },
	{ "DHAKA BANGLADESH" },
	{ "DURHAM NC" },
	{ "EL PASO TX" },
	{ "FORT WAYNE IN" },
	{ "FORT WORTH TX" },
	{ "FREMONT CA" },
	{ "FRESNO CA" },
	{ "FRIENDSWOOD TX" },
	{ "GARLAND TX" },
	{ "GILBERT AZ" },
	{ "GLENDALE AZ" },
	{ "GREENSBORO NC" },
	{ "GUADALAJARA MEXICO" },
	{ "GUANGZHOU CHINA" },
	{ "HAMBURG GERMANY" },
	{ "HANGZHOU CHINA" },
	{ "HENDERSON NV" },
	{ "HIALEAH FL" },
	{ "HONG KONG CHINA" },
	{ "HONOLULU HI" },
	{ "HOUSTON TX" },
	{ "HYDERABAD INDIA" },
	{ "INDIANAPOLIS IN" },
	{ "IRVINE CA" },
	{ "ISTANBUL TURKEY" },
	{ "JACKSONVILLE FL" },
	{ "JAKARTA INDONESIA" },
	{ "JERSEY CITY NJ" },
	{ "KANSAS  MO" },
	{ "KARACHI PAKISTAN" },
	{ "KOLKATA INDIA" },
	{ "LAGOS NIGERIA" },
	{ "LAREDO TX" },
	{ "LAS VEGAS NV" },
	{ "LEXINGTON KY" },
	{ "LIMA PERU" },
	{ "LINCOLN NE" },
	{ "LONDON UK" },
	{ "LONG BEACH CA" },
	{ "LOS ANGELES CA" },
	{ "LOUISVILLE KY" },
	{ "LUANDA ANGOLA" },
	{ "LUBBOCK TX" },
	{ "MADISON WA" },
	{ "MADISON WI" },
	{ "MADRID SPAIN" },
	{ "MANILA PHILIPPINES" },
	{ "MELBOURNE AUSTRALIA" },
	{ "MEMPHIS TN" },
	{ "MESA AZ" },
	{ "MEXICO CITY MEXICO" },
	{ "MIAMI FL" },
	{ "MILAN ITALY" },
	{ "MILWAUKEE WA" },
	{ "MINNEAPOLIS MN" },
	{ "MONTERREY MEXICO" },
	{ "MONTGOMERY WV" },
	{ "MUMBAI INDIA" },
	{ "MUNICH GERMANY" },
	{ "NAGOYA JAPAN" },
	{ "NANCHANG CHINA" },
	{ "NANJING CHINA" },
	{ "NASHVILLE TN" },
	{ "NEW DELHI INDIA" },
	{ "NEW ORLEANS LA" },
	{ "NEW YORK NY" },
	{ "NEWARK NJ" },
	{ "NORFOLK VA" },
	{ "OAKLAND CA" },
	{ "OKLAHOMA CITY OK" },
	{ "OMAHA NE" },
	{ "ORLANDO FL" },
	{ "OSAKA JAPAN" },
	{ "PARIS FRANCE" },
	{ "PHILADELPHIA PA" },
	{ "PHOENIX AZ" },
	{ "PITTSBURGH PA" },
	{ "PLANO TX" },
	{ "PORTLAND OR" },
	{ "PUNE INDIA" },
	{ "QINGDAO CHINA" },
	{ "RALEIGH NC" },
	{ "RENO NV" },
	{ "RHINE RUHR GERMANY" },
	{ "RICHMOND VA" },
	{ "RIO DE JANEIRO BR" },
	{ "RIVERSIDE CA" },
	{ "ROME ITALY" },
	{ "SACRAMENTO CA" },
	{ "SAN ANTONIO TX" },
	{ "SAN BERNARDINO CA" },
	{ "SAN DIEGO CA" },
	{ "SAN FRANCISCO CA" },
	{ "SAN JOSE CA" },
	{ "SANTIAGO CHILE" },
	{ "SAO PAULO BRAZIL" },
	{ "SCOTTSDALE AZ" },
	{ "SEATTLE WA" },
	{ "SEOUL SOUTH KOREA" },
	{ "SHANGHAI CHINA" },
	{ "SHENYANG CHINA" },
	{ "SHENZHEN CHINA" },
	{ "ST LOUIS MO" },
	{ "ST PAUL MN" },
	{ "ST PETERSBURG FL" },
	{ "STUTTGART GERMANY" },
	{ "SURAT INDIA" },
	{ "SYDNEY AUSTRALIA" },
	{ "TAIPEI TAIWAN" },
	{ "TAMPA FL" },
	{ "TEHRAN IRAN" },
	{ "TIANJIN CHINA" },
	{ "TOKYO JAPAN" },
	{ "TOLEDO OH" },
	{ "TORONTO CANADA" },
	{ "TUCSON AZ" },
	{ "TULSA OK" },
	{ "VIRGINIA BEACH VA" },
	{ "WASHINGTON DC" },
	{ "WENZHOU CHINA" },
	{ "WICHITA KS" },
	{ "WINSTON NC" },
	{ "WUHAN CHINA" },
	{ "XIAN CHINA" },
	{ "ZHENGZHOU CHINA" }
};

// QSO parts

const BHMorse_QSOPart BHMorse::_QSOParts[BHMORSE_QSOPART_NUMROW] PROGMEM =
{
	{" TNX FER CALL"},		// FB1
	{" FB"},							// FB2
	{""},									// FB3
	{" DE "},							// DE
	{" = UR RST IS "},		// RST1
	{" = RST "},					// RST2
	{" = NAME IS "},			// Name1
	{" = NAME "},					// Name2
	{" = QTH IS "},				// QTH1
	{" = QTH "},					// QTH2
	{" = BK TO YOU "},		// Bk2U1
	{" = "},							// Bk2U2
	{" K "},							// K1
	{" ("}								// K2 {KN}
};

// temporary buffer for building messages

char _tmpBuffer[BHMORSE_MESSAGE_BUFRSIZE];

//////////////////////////////////////////////////////////////////////////////
// Character map
//////////////////////////////////////////////////////////////////////////////

const BHMorse::charElement BHMorse::_charElemMap[BHMORSE_CHAR_ELEMENT_MAP_LENGTH] PROGMEM =
{

	{8,  7, 0x00000000}, // inter-character space
	{7, 19, 0xEBAEE000}, // !
	{6, 15, 0xBABA0000}, // "
	{5, 15, 0xABAE0000}, // # {SK}
	{7, 17, 0xABAB8000}, // $
	{7, 11, 0xABA00000}, // % {SN}
	{9, 15, 0xEBAE0000}, // & {CT}/{KA} start of message
	{7, 19, 0xBBBBA000}, // '
	{5, 15, 0xEBBA0000}, // ( also {KN}
	{7, 19, 0xEBBAE000}, // )
	{6, 11, 0xBAE00000}, // * {AA} new line
	{7, 13, 0xBAE80000}, // + also {AR} new page
	{5, 19, 0xEEAEE000}, // ,
	{7, 15, 0xEAAE0000}, // -
	{5, 17, 0xBAEB8000}, // .
	{5, 13, 0xEAE80000}, // /
	{4, 19, 0xEEEEE000}, // 0
	{4, 17, 0xBBBB8000}, // 1
	{4, 15, 0xAEEE0000}, // 2
	{4, 13, 0xABB80000}, // 3
	{4, 11, 0xAAE00000}, // 4
	{4,  9, 0xAA800000}, // 5
	{4, 11, 0xEAA00000}, // 6
	{4, 13, 0xEEA80000}, // 7
	{4, 15, 0xEEEA0000}, // 8
	{4, 17, 0xEEEE8000}, // 9
	{7, 17, 0xEEEA8000}, // :
	{7, 17, 0xEBAE8000}, // ;
	{9,  0, 0x00000000}, // < UNUSED
	{5, 13, 0xEAB80000}, // =
	{9,  0, 0x00000000}, // > UNUSED
	{5, 15, 0xAEEA0000}, // ?
	{6, 17, 0xBBAE8000}, // @
	{1,  5, 0xB8000000}, // A
	{3,  9, 0xEA800000}, // B
	{3, 11, 0xEBA00000}, // C
	{2,  7, 0xEA000000}, // D
	{1,  1, 0x80000000}, // E
	{3,  9, 0xAE800000}, // F
	{2,  9, 0xEE800000}, // G
	{2,  7, 0xAA000000}, // H
	{1,  3, 0xA0000000}, // I
	{3, 13, 0xBBB80000}, // J
	{2,  9, 0xEB800000}, // K
	{3,  9, 0xBA800000}, // L
	{1,  7, 0xEE000000}, // M
	{1,  5, 0xE8000000}, // N
	{2, 11, 0xEEE00000}, // O
	{3, 11, 0xBBA00000}, // P
	{3, 13, 0xEEB80000}, // Q
	{2,  7, 0xBA000000}, // R
	{1,  5, 0xA8000000}, // S
	{1,  3, 0xE0000000}, // T
	{2,  7, 0xAE000000}, // U
	{3,  9, 0xAB800000}, // V
	{2,  9, 0xBB800000}, // W
	{3, 11, 0xEAE00000}, // X
	{3, 13, 0xEBB80000}, // Y
	{3, 11, 0xEEA00000}, // Z
	{9,  0, 0x00000000}, // [ UNUSED
	{6, 23, 0xABBBAA00}, // "\" {SOS}
	{9,  0, 0x00000000}, // ] UNUSED
	{3, 15, 0xAAAA0000}, // ^ {HH} error
	{7, 17, 0xAEEB8000}, // _
	{5, 11, 0xBAA00000}  // ` {AS} wait
};

void BHMorse::getRandomName(char* retV)
{
	// return a random name from the table in PROGMEM

	int r = random(0, BHMORSE_FIRSTNAME_NUMROW);

	BHMorse_FirstName buffer;
	memcpy_P(&buffer, &_firstNames[r], sizeof(buffer));
	strcpy(retV, buffer.d);
}

void BHMorse::getRandomCity(char* retV)
{
	// return a random city from the table in PROGMEM

	int r = random(0, BHMORSE_CITY_NUMROW);

	BHMorse_City buffer;
	memcpy_P(&buffer, &_cities[r], sizeof(buffer));
	strcpy(retV, buffer.d);
}

void BHMorse::getRandomCall(char* retV)
{
	// return a random callsign
	//
	// 1-2 letters
	// 1 number
	// 1-3 letters
	// but fix A1A to A1AA

	byte n;
	byte p;
	byte l;

	// empty

	strcpy(retV, "");

	// prefix

	///TODO: only use legal IARU prefixes

	n = random(1, 3);
	for (byte i = 0; i < n; i++)
	{
		p = random('A', 'Z' + 1);
		l = strlen(retV);
		retV[l] = p;
		retV[l + 1] = '\0';
	}

	// number

	p = random('0', '9' + 1);
	l = strlen(retV);
	retV[l] = p;
	retV[l + 1] = '\0';

	// suffix

	n = random(4 - strlen(retV), 4);	// if "A1" so far, force suffix to >= 2 chars
	for (byte i = 0; i < n; i++)
	{
		p = random('A', 'Z' + 1);
		l = strlen(retV);
		retV[l] = p;
		retV[l + 1] = '\0';
	}
}

void BHMorse::getRandomRST(char* retV)
{
	// random RST
	//
	// [3-5]
	// [4-9]
	// [7-9]

	strcpy(retV, "");
	retV[0] = random('3', '5' + 1);
	retV[1] = random('4', '9' + 1);
	retV[2] = random('7', '9' + 1);
	retV[3] = '\0';
}

BHMorse::charElement BHMorse::getCharElement(int p)
{
	// read a character from PROGMEM

	charElement retV;
	memcpy_P(&retV, &_charElemMap[p], sizeof(charElement));
	return retV;
}

void BHMorse::getQSOPart(char* retV, int p)
{
	// read a QSO part from PROGMEM

	BHMorse_QSOPart b;
	memcpy_P(&b, &_QSOParts[p], sizeof(BHMorse_QSOPart));
	strcpy(retV, b.d);
}

void BHMorse::redoCharGroupPtrs()
{
	// populate the character group pointer table

	_numCharGroupPtrs = 0;

	for (int i = 0; i < BHMORSE_CHAR_ELEMENT_MAP_LENGTH; i++)
	{
		charElement c = getCharElement(i);
		if (c.charGroup <= highestEnabledGroup())
		{
			_ptrsToCharsInGroupRange[_numCharGroupPtrs] = i;
			_numCharGroupPtrs++;
		}
	}
}

boolean BHMorse::isSpace(charElement pChar)
{
	// returns true if the passed character is a space

	return (pChar.charGroup == BHMORSE_CHAR_ELEMENT_MAP_GROUP_SPACE);
}

void BHMorse::loadChar()
{
	_tempChar = BHMORSE_CHAR_ELEMENT_MAP_UNUSED;
	_numElemsInCharSent = 0;

	// load a copy of the next character to be sent

	if (strlen(_message) > 0)
	{
		byte c = _message[_numCharsInMsgSent];
		int c2s = c - BHMORSE_CHAR_ELEMENT_MAP_OFFSET;

		// see if it's a valid index into the character map:

		if ((c2s >= 0) &&
				(c2s < BHMORSE_CHAR_ELEMENT_MAP_LENGTH))
		{
			_tempChar = getCharElement(c2s);
		}
	}
}

void BHMorse::loadNextChar()
{
	// load next random character to send with group <= highestEnabledGroup

	int rndChar = random(0, _numCharGroupPtrs);
	_tmpBuffer[0] = _ptrsToCharsInGroupRange[rndChar] + BHMORSE_CHAR_ELEMENT_MAP_OFFSET;
	_tmpBuffer[1] = '\0';
	setMessage(_tmpBuffer);
}

void BHMorse::loadNextGroup()
{
	// load next group of random characters with group <= highestEnabledGroup

	byte rndNumChars = random(BHMORSE_RANDOMGROUP_MIN, BHMORSE_RANDOMGROUP_MAX + 1);
	byte rndChar;

	for (int i = 0; i < rndNumChars; i++)
	{
		rndChar = random(0, _numCharGroupPtrs);
		_tmpBuffer[i] = char(_ptrsToCharsInGroupRange[rndChar] + BHMORSE_CHAR_ELEMENT_MAP_OFFSET);
	}
	_tmpBuffer[rndNumChars] = '\0';

	setMessage(_tmpBuffer);
}

void BHMorse::loadNextQSO()
{
	// load next random QSO

	char bufr[BHMORSE_CITY_MAXLEN];		// buffer large enough to hold largest part
	byte p;

	strcpy(_tmpBuffer, "");

	// get calls

	char callA[10];
	getRandomCall(callA);

	char callB[10];
	getRandomCall(callB);

	// calla DE callb

	strcpy(_tmpBuffer, callA);

	getQSOPart(bufr, BHMorse_QSOPart_Row::DE);
	strcat(_tmpBuffer, bufr);

	strcat(_tmpBuffer, callB);

	// FB

	p = random(BHMorse_QSOPart_Row::FB1, BHMorse_QSOPart_Row::FB3 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	// RST

	p = random(BHMorse_QSOPart_Row::RST1, BHMorse_QSOPart_Row::RST2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	getRandomRST(bufr);
	strcat(_tmpBuffer, bufr);

	// Name

	p = random(BHMorse_QSOPart_Row::Name1, BHMorse_QSOPart_Row::Name2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	getRandomName(bufr);
	strcat(_tmpBuffer, bufr);

	// QTH

	p = random(BHMorse_QSOPart_Row::QTH1, BHMorse_QSOPart_Row::QTH2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	getRandomCity(bufr);
	strcat(_tmpBuffer, bufr);

	// Back to you

	p = random(BHMorse_QSOPart_Row::Bk2U1, BHMorse_QSOPart_Row::Bk2U2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	// calla DE callb

	strcat(_tmpBuffer, callA);

	getQSOPart(bufr, BHMorse_QSOPart_Row::DE);
	strcat(_tmpBuffer, bufr);

	strcat(_tmpBuffer, callB);

	// K

	p = random(BHMorse_QSOPart_Row::K1, BHMorse_QSOPart_Row::K2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	// send it

	setMessage(_tmpBuffer);
}

//////////////////////////////////////////////////////////////////////////////
// constructors
//////////////////////////////////////////////////////////////////////////////

BHMorse::BHMorse()
{
	// constructor
	// put stuff you don't want to do until main.setup() in begin()

	// stop running

	_runMode = Idle;

	// reset some things

	_numCharGroupPtrs = 0;	// just in case
}

//////////////////////////////////////////////////////////////////////////////
// Morse parameter getters for backed properties
//////////////////////////////////////////////////////////////////////////////

BHMorse_WpmFactor BHMorse::wpmSchemeFactor()
{
	return _wpmSchemeFactor;
}

BHMorse_Wpm BHMorse::overallSpeed()
{
	return _overallSpeed;
}

BHMorse_Wpm BHMorse::userCharSpeed()
{
	return _userCharSpeed;
}

BHMorse_charElemMap_Group BHMorse::highestEnabledGroup()
{
	return _highestEnabledGroup;
}

//////////////////////////////////////////////////////////////////////////////
// Morse parameter getters for computed properties
//////////////////////////////////////////////////////////////////////////////

BHMorse_Wpm BHMorse::charSpeed()
{
	// the actual character (dit mark) speed that we'll use;
	// this is "c" in the ARRL calculations

	int retV = 0;

	if (overallSpeed() >= BHMORSE_FARNSWORTH_CAP)
	{
		retV = overallSpeed();
	}
	else
	{
		retV = max(userCharSpeed(), overallSpeed());
	}

	return retV;
}

BHMorse_Duration BHMorse::charDitMarkTime()
{
	// the character speed dit mark time
	// this is "u" in ARRL calculations

	BHMorse_Duration retV = 0;

	if (charSpeed() != 0)
	{
		retV = wpmSchemeFactor() / charSpeed();
	}

	return retV;
}

BHMorse_Duration BHMorse::charDitSpaceTime()
{
	// the character dit space time;
	// we're at a fixed Weight of 0.50

	return charDitMarkTime();
}

BHMorse_Duration BHMorse::charDahMarkTime()
{
	// the character dah mark time;
	// we're at a fixed Ratio of BHMORSE_DITS_PER_DAH

	return (charDitMarkTime() * BHMORSE_DITS_PER_DAH);
}

BHMorse_Duration BHMorse::farnsworthDelayTime()
{
	// the Farnsworth delay factor;
	// this is t(a) in ARRL calculations

	double numerator = ((60.0 * charSpeed()) - (37.2 * overallSpeed())) * 1000;
	double denominator = (charSpeed() * overallSpeed());
	BHMorse_Duration retV = numerator / denominator;

	return retV;
}

BHMorse_Duration BHMorse::interCharSpaceTime()
{
	// the time between characters;
	// this is t(c) in ARRL calculations

	return ((BHMORSE_DITS_PER_DAH * farnsworthDelayTime()) / 19);
}

BHMorse_Duration BHMorse::interWordSpaceTime()
{
	// the time between words:
	// this is t(w) in ARRL calculations

	return ((BHMORSE_DITS_PER_CHARSPACE * farnsworthDelayTime()) / 19);
}

//////////////////////////////////////////////////////////////////////////////
// Morse parameter setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setWpmSchemeFactor(BHMorse_WpmFactor newValue)
{
	if (true)
	{
		_wpmSchemeFactor = newValue;
	}
}

void BHMorse::setOverallSpeed(BHMorse_Wpm newValue)
{
	if ((newValue >= BHMORSE_MIN_WPM) &&
			(newValue <= BHMORSE_MAX_WPM))
	{
		_overallSpeed = newValue;
		saveOverallSpeed();
	}
}

void BHMorse::setUserCharSpeed(BHMorse_Wpm newValue)
{
	if ((newValue >= BHMORSE_MIN_WPM) &&
			(newValue <= BHMORSE_MAX_WPM))
	{
		_userCharSpeed = newValue;
		saveUserCharSpeed();
	}
}

void BHMorse::setHighestEnabledGroup(BHMorse_charElemMap_Group newValue)
{
	if ((newValue >= BHMORSE_MIN_CHARACTER_GROUP) &&
			(newValue <= BHMORSE_MAX_CHARACTER_GROUP))
	{
		_highestEnabledGroup = newValue;
		saveHighestEnabledGroup();
		redoCharGroupPtrs();
	}
}

//////////////////////////////////////////////////////////////////////////////
// sound parameter getters
//////////////////////////////////////////////////////////////////////////////

int BHMorse::tonePin()
{
	return _tonePin;
}

BHMorse_Hz BHMorse::pitch()
{
	return _pitch;
}

//////////////////////////////////////////////////////////////////////////////
// sound parameter setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setTonePin(int newValue)
{
	_tonePin = newValue;
	pinMode(_tonePin, OUTPUT);
	noTone(_tonePin);
}

void BHMorse::setPitch(BHMorse_Hz newValue, bool pSave)
{
	if ((newValue >= BHMORSE_MIN_PITCH) &&
			(newValue <= BHMORSE_MAX_PITCH))
	{
		_pitch = newValue;
		if (pSave) savePitch();
	}
}

//////////////////////////////////////////////////////////////////////////////
// message parameter getters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::message(char* retV)
{
	strcpy(retV, _message);
}

//////////////////////////////////////////////////////////////////////////////
// message paremeter setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setMessage(char const* newValue)
{
#ifdef BHMORSE_DEBUG
	if (strlen(newValue) > 0)
	{
		Serial.print(F("Message = '"));
		Serial.print(newValue);
		Serial.println(F("'"));
	}
#endif

	strcpy(_message, newValue);

	// load 1st character

	_numCharsInMsgSent = 0;
	
	loadChar();
}

//////////////////////////////////////////////////////////////////////////////
// other getters
//////////////////////////////////////////////////////////////////////////////

BHMorse::RunMode BHMorse::runMode()
{
	return _runMode;
}

//////////////////////////////////////////////////////////////////////////////
// other setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setRunMode(BHMorse::RunMode newValue)
{
	_runMode = newValue;

	setMessage("");

	// if it's one of the random run modes, prime the first message

	switch (runMode())
	{
		case Idle:
			break;

		case SendChars:
			loadNextChar();
			break;

		case SendGroups:
			loadNextGroup();
			break;

		case SendQSOs:
			loadNextQSO();
			break;

		default:
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////
// EEPROM settings stuff
//////////////////////////////////////////////////////////////////////////////

BHMorse_EEPROMSignature BHMorse::readSignature()
{
	// read signature

	BHMorse_EEPROMSignature es = 0;
	EEPROM.get(BHMORSE_EEPROM_ADDR_SIGNATURE, es);

	return es;
}

void BHMorse::readOverallSpeed()
{
	// read signature

	BHMorse_Wpm tmpWpm;
	EEPROM.get(BHMORSE_EEPROM_ADDR_OVERALLSPEED, tmpWpm);
	setOverallSpeed(tmpWpm);
}

void BHMorse::readUserCharSpeed()
{
	// save user character speed

	BHMorse_Wpm tmpWpm;
	EEPROM.get(BHMORSE_EEPROM_ADDR_USERCHARSPEED, tmpWpm);
	setUserCharSpeed(tmpWpm);
}

void BHMorse::readHighestEnabledGroup()
{
	// save highest enabled group

	BHMorse_charElemMap_Group tmpGroup;
	EEPROM.get(BHMORSE_EEPROM_ADDR_HIGHESTENABLEDGROUP, tmpGroup);
	setHighestEnabledGroup(tmpGroup);
}

void BHMorse::readPitch()
{
	// save pitch

	BHMorse_Hz tmpHz;
	EEPROM.get(BHMORSE_EEPROM_ADDR_PITCH, tmpHz);
	setPitch(tmpHz, true);
}

void BHMorse::loadSettings()
{
	// read persistent settings to EEPROM

	if (readSignature() == BHMORSE_EEPROM_SIGNATURE_V1)
	{
		// get settings from EEPROM

		readOverallSpeed();
		readUserCharSpeed();
		readHighestEnabledGroup();
		readPitch();
	}
	else
	{
		// new defaults

		resetSettings();
	}
}

void BHMorse::resetSettings()
{
	// reset settings to factor defaults

	saveSignature();
	setOverallSpeed(BHMORSE_DEFAULT_OVERALLSPEED);
	setUserCharSpeed(BHMORSE_DEFAULT_USERCHARSPEED);
	setHighestEnabledGroup(BHMORSE_DEFAULT_HIGHESTENABLEDGROUP);
	setPitch(BHMORSE_DEFAULT_PITCH, true);
}

void BHMorse::saveSignature()
{
	BHMorse_EEPROMSignature es = BHMORSE_EEPROM_SIGNATURE_V1;
	EEPROM.put(BHMORSE_EEPROM_ADDR_SIGNATURE, es);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::saveOverallSpeed()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_OVERALLSPEED, _overallSpeed);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::saveUserCharSpeed()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_USERCHARSPEED, _userCharSpeed);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::saveHighestEnabledGroup()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_HIGHESTENABLEDGROUP, _highestEnabledGroup);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::savePitch()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_PITCH, _pitch);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

//////////////////////////////////////////////////////////////////////////////
// other methods
//////////////////////////////////////////////////////////////////////////////

void BHMorse::begin(int tonePin)
{
	// do stuff that you can't or don't want to do in the constructor

	// seed the "random" # generator

	randomSeed(analogRead(BHMORSE_UNUSED_ANALOGPIN));

	// load settings from EEPROM

	loadSettings();

	// set WPM Factor

	setWpmSchemeFactor(BHMORSE_WPMSCHEMEFACTOR_PARIS);

	// install parameters

	setTonePin(tonePin);
}

boolean BHMorse::elemsRemainInChar()
{
	// returns true if any elements remain to be sent in the current character

	return (_numElemsInCharSent < _tempChar.numElems);
}

boolean BHMorse::charsRemainInMsg()
{
	// returns true if any characters remain to be send in the message

	return (_numCharsInMsgSent < strlen(_message));
}

boolean BHMorse::msgDone()
{
	// returns true if any elements remain to be sent in the current character,
	// or any characters remain to be send in the message

	return (!elemsRemainInChar() && !charsRemainInMsg());
}

void BHMorse::sendUntilMsgDone()
{
	// send elements until the message is done

	while (!msgDone())
	{
		sendNextElem();
	}
}

void BHMorse::sendMessage(const char* pMessage)
{
  // send a message and wait for it to finish

  setRunMode(SendMessage);
  setMessage(pMessage);
  sendUntilMsgDone();
}

void BHMorse::sendNextElem()
{
	// send the next element to be sent

	if (bitRead(_tempChar.elements, (BHMORSE_CHAR_ELEMENT_MAP_HIELEMENTBIT - _numElemsInCharSent)))
	{
		bool offAfter =
		(bitRead(_tempChar.elements,
						 (BHMORSE_CHAR_ELEMENT_MAP_HIELEMENTBIT - 1 - _numElemsInCharSent)) == 0);

		sendMark(offAfter);
	}
	else
	{
		sendSpace();
	}

	// bump element counter

	_numElemsInCharSent++;

	if (!elemsRemainInChar())
	{
		// character's finished

		// bump character counter

		_numCharsInMsgSent++;

		if (charsRemainInMsg())
		{
			// get next character

			loadChar();

			// if the next char isn't a space, wait inter-character space,
			// so we don't add inter-char space to inter-word space

			if (!isSpace(_tempChar))
			{
				waitInterCharSpace();
			}
		}
		else
		{
			// message is finished;
			// see if I need to load the next message

			switch (runMode())
			{
				case Idle:
					// weird; I shouldn't be here
					break;

				case SendMessage:
					// nothing to do next; go idle
					setRunMode(Idle);
					break;

				case SendChars:
					// wait:
					waitInterCharSpace();
					// load next character
					loadNextChar();
					break;

				case SendGroups:
					// wait
					waitInterWordSpace();
					// load next group
					loadNextGroup();
					break;

				case SendQSOs:
					// wait
					waitInterWordSpace();
					waitInterWordSpace();
					// load next QSO
					loadNextQSO();
					break;

				case SendFile:
					// nothing to do next; go idle
					setRunMode(Idle);

				default:
					// weird; I shouldn't be here
					setRunMode(Idle);
					break;
			}
		}
	}
}

void BHMorse::sendMark(bool pStopAfter)
{
	// send an element of mark

	tone(tonePin(), pitch());
	delay(charDitMarkTime());
	if (pStopAfter) noTone(tonePin());
}

void BHMorse::sendSpace()
{
	// send an element of space

	noTone(tonePin());
	waitInterElemSpace();
}

void BHMorse::beepHi()
{
	// beep high

	for (byte i = 0; i < BHMORSE_TONE_HI_1_LOOPS; i++)
	{
		tone(tonePin(), BHMORSE_TONE_HI_1_HZ);
		delay(BHMORSE_TONE_HI_1_DURATION);
		tone(tonePin(), BHMORSE_TONE_HI_2_HZ);
		delay(BHMORSE_TONE_HI_2_DURATION);
		noTone(tonePin());
	}
	delay(BHMORSE_TONE_HI_3_DURATION);
}

void BHMorse::beepLo()
{
	// beep low

	for (byte i = 0; i < BHMORSE_TONE_LO_1_LOOPS; i++)
	{
		tone(tonePin(), BHMORSE_TONE_LO_1_HZ);
		delay(BHMORSE_TONE_LO_1_DURATION);
		tone(tonePin(), BHMORSE_TONE_LO_2_HZ);
		delay(BHMORSE_TONE_LO_2_DURATION);
		noTone(tonePin());
	}
	delay(BHMORSE_TONE_LO_3_DURATION);
}

void BHMorse::waitInterElemSpace()
{
	// wait the time between elements

	delay(charDitSpaceTime());
}

void BHMorse::waitInterCharSpace()
{
	// wait the time between characters

	delay(interCharSpaceTime());
}

void BHMorse::waitInterWordSpace()
{
	// wait the time between words

	delay(interWordSpaceTime());
}
