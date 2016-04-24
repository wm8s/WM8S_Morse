//////////////////////////////////////////////////////////////////////////////
//
//	BHMorse.cpp - Library for Morse code
//
//	Created 2016-04-01 by Rob Bailey, WM8S
//
//	Send Morse Code, including generating random characters, groups of
//	characters, or plausible QSOs.
//
//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <EEPROM.h>
#include "BHMorse.h"

//////////////////////////////////////////////////////////////////////////////
// Stuff available for random senders
//////////////////////////////////////////////////////////////////////////////

// names

const BHMorse_FirstName BHMorse::_firstNames[] PROGMEM =
{
	{ "AARAV" },
	{ "ADI" },
	{ "AGUSTIN" },
	{ "AI" },
	{ "ALEX" },
	{ "ALEXANDER" },
	{ "AMANDA" },
	{ "AMIT" },
	{ "AMY" },
	{ "ANDREAS" },
	{ "ANDREI" },
	{ "ANDY" },
	{ "ANGEL" },
	{ "ANGELA" },
	{ "ANNA" },
	{ "ANSON" },
	{ "ANTONIO" },
	{ "ARATA" },
	{ "ARIEL" },
	{ "ARON" },
	{ "ASAHI" },
	{ "ASHER" },
	{ "ASHLEY" },
	{ "ATTICUS" },
	{ "AVA" },
	{ "AYA" },
	{ "AZIZ" },
	{ "BARB" },
	{ "BARBARA" },
	{ "BARBIE" },
	{ "BEN" },
	{ "BETTY" },
	{ "BILL" },
	{ "BOB" },
	{ "BOBBIE" },
	{ "BRANDON" },
	{ "BRENDA" },
	{ "BRIAN" },
	{ "BRUNO" },
	{ "CAROL" },
	{ "CAROLYN" },
	{ "CATHY" },
	{ "CHARLES" },
	{ "CHRIS" },
	{ "CHRISTINE" },
	{ "CYNTHIA" },
	{ "DANIEL" },
	{ "DAVE" },
	{ "DAVID" },
	{ "DAVIT" },
	{ "DEBORAH" },
	{ "DEBRA" },
	{ "DECLAN" },
	{ "DENNIS" },
	{ "DEREK" },
	{ "DIANE" },
	{ "DICK" },
	{ "DIEGO" },
	{ "DONALD" },
	{ "DONNA" },
	{ "DOROTHY" },
	{ "ED" },
	{ "ELEANOR" },
	{ "ELIAS" },
	{ "EMILY" },
	{ "ERIC" },
	{ "EZRA" },
	{ "FAITH" },
	{ "FENG" },
	{ "FILIP" },
	{ "FRANCESCO" },
	{ "FRANCISCO" },
	{ "FRANK" },
	{ "FREJA" },
	{ "GARY" },
	{ "GEORGE" },
	{ "GEORGI" },
	{ "GOR" },
	{ "GRACE" },
	{ "GREG" },
	{ "HANK" },
	{ "HANS" },
	{ "HAO" },
	{ "HARUKI" },
	{ "HARUTA" },
	{ "HEATHER" },
	{ "HELEN" },
	{ "HINATA" },
	{ "HIROTO" },
	{ "HUGO" },
	{ "IAN" },
	{ "ICHIKA" },
	{ "IOANNIS" },
	{ "ITSUKI" },
	{ "JACK" },
	{ "JACKSON" },
	{ "JACOB" },
	{ "JAKOB" },
	{ "JAMES" },
	{ "JAN" },
	{ "JANE" },
	{ "JANET" },
	{ "JASON" },
	{ "JASPER" },
	{ "JAVIER" },
	{ "JAYDEN" },
	{ "JEFF" },
	{ "JENNIFER" },
	{ "JERRY" },
	{ "JESSICA" },
	{ "JIAN" },
	{ "JIE" },
	{ "JIM" },
	{ "JOAO" },
	{ "JOE" },
	{ "JOHN" },
	{ "JONAS" },
	{ "JOSE" },
	{ "JOSEPH" },
	{ "JOSHUA" },
	{ "JUAN" },
	{ "JUN" },
	{ "JUSTIN" },
	{ "KAREN" },
	{ "KEN" },
	{ "KEVIN" },
	{ "KIM" },
	{ "LARA" },
	{ "LARRY" },
	{ "LARS" },
	{ "LAURA" },
	{ "LEXI" },
	{ "LIAM" },
	{ "LINDA" },
	{ "LINDSEY" },
	{ "LISA" },
	{ "LIZ" },
	{ "LUCIA" },
	{ "LUIS" },
	{ "LUKAS" },
	{ "MAIA" },
	{ "MALIK" },
	{ "MARC" },
	{ "MARGARET" },
	{ "MARIA" },
	{ "MARK" },
	{ "MARY" },
	{ "MASON" },
	{ "MATEO" },
	{ "MATHIS" },
	{ "MATIAS" },
	{ "MATT" },
	{ "MAXIM" },
	{ "MAYA" },
	{ "MEHMET" },
	{ "MICHAEL" },
	{ "MICHELLE" },
	{ "MIGUEL" },
	{ "MIKE" },
	{ "MILO" },
	{ "MIN JOON" },
	{ "MINATO" },
	{ "MISSY" },
	{ "MOSHE" },
	{ "NANCY" },
	{ "NAREK" },
	{ "NICK" },
	{ "NICOLAS" },
	{ "NICOLE" },
	{ "NOA" },
	{ "NOAH" },
	{ "NOAM" },
	{ "OLIVER" },
	{ "OLIVIA" },
	{ "OMAR" },
	{ "ONNI" },
	{ "PABLO" },
	{ "PAMELA" },
	{ "PAT" },
	{ "PATRICK" },
	{ "PATTIE" },
	{ "PATTY" },
	{ "PAUL" },
	{ "PEDRO" },
	{ "PENELOPE" },
	{ "QIAN" },
	{ "RACHEL" },
	{ "RAYMOND" },
	{ "REBECCA" },
	{ "REN" },
	{ "RENZ" },
	{ "RICH" },
	{ "RICHARD" },
	{ "RICHIE" },
	{ "RICK" },
	{ "RIKO" },
	{ "ROB" },
	{ "ROD" },
	{ "RODNEY" },
	{ "RODRIGO" },
	{ "RON" },
	{ "RUTH" },
	{ "RYAN" },
	{ "SAKURA" },
	{ "SAM" },
	{ "SAMUEL" },
	{ "SANDY" },
	{ "SANTIAGO" },
	{ "SARAH" },
	{ "SCOTT" },
	{ "SEBASTIAN" },
	{ "SHANE" },
	{ "SHARON" },
	{ "SHIRA" },
	{ "SHIRLEY" },
	{ "SHU" },
	{ "SOMCHAI" },
	{ "SOMSAK" },
	{ "SOPHIA" },
	{ "SOU" },
	{ "SOUTA" },
	{ "STEPH" },
	{ "STEPHEN" },
	{ "STEVE" },
	{ "SUE" },
	{ "TALIA" },
	{ "TAMAR" },
	{ "TATSUKI" },
	{ "THOMAS" },
	{ "TIBERIUS" },
	{ "TIM" },
	{ "TODD" },
	{ "TOM" },
	{ "TOMAS" },
	{ "TOMMY" },
	{ "TOMOHARU" },
	{ "TONY" },
	{ "TSURUKI" },
	{ "VIRGINIA" },
	{ "WEI" },
	{ "WILL" },
	{ "WILLIAM" },
	{ "WOUT" },
	{ "XIAN" },
	{ "YAEL" },
	{ "YI" },
	{ "YONG" },
	{ "YUSUF" },
	{ "YUUMA" },
	{ "YUVAL" }
};

// cities

const BHMorse_City BHMorse::_cities[] PROGMEM =
{
	{ "ABILENE TX" },
	{ "AHMEDABAD INDIA" },
	{ "AKRON OH" },
	{ "ALBUQUERQUE NM" },
	{ "ALEXANDRIA VA" },
	{ "ALLENTOWN PA" },
	{ "AMARILLO TX" },
	{ "ANAHEIM CA" },
	{ "ANCHORAGE AK" },
	{ "ANKARA TURKEY" },
	{ "ANN ARBOR MI" },
	{ "ANTIOCH CA" },
	{ "ARLINGTON TX" },
	{ "ARVADA CO" },
	{ "ATHENS GA" },
	{ "ATLANTA GA" },
	{ "AUGUSTA GA" },
	{ "AURORA CO" },
	{ "AURORA IL" },
	{ "AUSTIN TX" },
	{ "BAKERSFIELD CA" },
	{ "BALTIMORE MD" },
	{ "BANGALORE INDIA" },
	{ "BANGKOK THAILAND" },
	{ "BARCELONA SPAIN" },
	{ "BATON ROUGE LA" },
	{ "BEAUMONT TX" },
	{ "BEIJING CHINA" },
	{ "BELLEVUE WA" },
	{ "BELO HORIZONTE BR" },
	{ "BERKELEY CA" },
	{ "BERLIN GERMANY" },
	{ "BILLINGS MT" },
	{ "BIRMINGHAM AL" },
	{ "BOGOTA COLOMBIA" },
	{ "BOISE ID" },
	{ "BOSTON MA" },
	{ "BOULDER CO" },
	{ "BRIDGEPORT CT" },
	{ "BROKEN ARROW OK" },
	{ "BROWNSVILLE TX" },
	{ "BUFFALO NY" },
	{ "BURBANK CA" },
	{ "CAMBRIDGE MA" },
	{ "CAPE CORAL FL" },
	{ "CARLSBAD CA" },
	{ "CARROLLTON TX" },
	{ "CARY NC" },
	{ "CEDAR RAPIDS IA" },
	{ "CENTENNIAL CO" },
	{ "CHANDLER AZ" },
	{ "CHARLESTON SC" },
	{ "CHARLESTON WV" },
	{ "CHARLOTTE NC" },
	{ "CHATTANOOGA TN" },
	{ "CHENGDU CHINA" },
	{ "CHENNAI INDIA" },
	{ "CHESAPEAKE VA" },
	{ "CHEYENNE WY" },
	{ "CHICAGO IL" },
	{ "CHONGQING CHINA" },
	{ "CHULA VISTA CA" },
	{ "CINCINNATI OH" },
	{ "CLARKSVILLE TN" },
	{ "CLEARWATER FL" },
	{ "CLEVELAND OH" },
	{ "CLOVIS CA" },
	{ "COLLEGE STATION TX" },
	{ "COLORADO SPRINGS CO" },
	{ "COLUMBIA MO" },
	{ "COLUMBIA SC" },
	{ "COLUMBUS GA" },
	{ "COLUMBUS OH" },
	{ "CONCORD CA" },
	{ "CORAL SPRINGS FL" },
	{ "CORONA CA" },
	{ "CORPUS CHRISTI TX" },
	{ "COSTA MESA CA" },
	{ "DALLAS TX" },
	{ "DALY CITY CA" },
	{ "DAVENPORT IA" },
	{ "DAYTON OH" },
	{ "DENTON TX" },
	{ "DENVER CO" },
	{ "DES MOINES IA" },
	{ "DETROIT MI" },
	{ "DHAKA BANGLADESH" },
	{ "DOWNEY CA" },
	{ "DURHAM NC" },
	{ "EDISON NJ" },
	{ "EL CAJON CA" },
	{ "EL MONTE CA" },
	{ "EL PASO TX" },
	{ "ELGIN IL" },
	{ "ELIZABETH NJ" },
	{ "ELK GROVE CA" },
	{ "ESCONDIDO CA" },
	{ "EUGENE OR" },
	{ "EVANSVILLE IN" },
	{ "EVERETT WA" },
	{ "FAIRFIELD CA" },
	{ "FARGO ND" },
	{ "FAYETTEVILLE NC" },
	{ "FONTANA CA" },
	{ "FORT COLLINS CO" },
	{ "FORT LAUDERDALE FL" },
	{ "FORT WAYNE IN" },
	{ "FORT WORTH TX" },
	{ "FREMONT CA" },
	{ "FRESNO CA" },
	{ "FRIENDSWOOD TX" },
	{ "FRISCO TX" },
	{ "FULLERTON CA" },
	{ "GAINESVILLE FL" },
	{ "GARDEN GROVE CA" },
	{ "GARLAND TX" },
	{ "GILBERT AZ" },
	{ "GLENDALE AZ" },
	{ "GLENDALE CA" },
	{ "GRAND PRAIRIE TX" },
	{ "GRAND RAPIDS MI" },
	{ "GREEN BAY WI" },
	{ "GREENSBORO NC" },
	{ "GRESHAM OR" },
	{ "GUADALAJARA MEXICO" },
	{ "GUANGZHOU CHINA" },
	{ "HAMBURG GERMANY" },
	{ "HAMPTON VA" },
	{ "HANGZHOU CHINA" },
	{ "HARTFORD CT" },
	{ "HAYWARD CA" },
	{ "HENDERSON NV" },
	{ "HIALEAH FL" },
	{ "HIGH POINT NC" },
	{ "HOLLYWOOD FL" },
	{ "HONG KONG CHINA" },
	{ "HONOLULU HI" },
	{ "HOUSTON TX" },
	{ "HUNTINGTON BEACH CA" },
	{ "HUNTSVILLE AL" },
	{ "HYDERABAD INDIA" },
	{ "INDEPENDENCE MO" },
	{ "INDIANAPOLIS IN" },
	{ "INGLEWOOD CA" },
	{ "IRVINE CA" },
	{ "IRVING TX" },
	{ "ISTANBUL TURKEY" },
	{ "JACKSON MS" },
	{ "JACKSONVILLE FL" },
	{ "JAKARTA INDONESIA" },
	{ "JERSEY CITY NJ" },
	{ "JOLIET IL" },
	{ "KANSAS  MO" },
	{ "KANSAS CITY KS" },
	{ "KANSAS CITY MO" },
	{ "KARACHI PAKISTAN" },
	{ "KENT WA" },
	{ "KILLEEN TX" },
	{ "KNOXVILLE TN" },
	{ "KOLKATA INDIA" },
	{ "LAFAYETTE LA" },
	{ "LAGOS NIGERIA" },
	{ "LAKELAND FL" },
	{ "LAKEWOOD CO" },
	{ "LANCASTER CA" },
	{ "LANSING MI" },
	{ "LAREDO TX" },
	{ "LAS CRUCES NM" },
	{ "LAS VEGAS NV" },
	{ "LEWISVILLE TX" },
	{ "LEXINGTON KY" },
	{ "LIMA PERU" },
	{ "LINCOLN NE" },
	{ "LITTLE ROCK AR" },
	{ "LONDON UK" },
	{ "LONG BEACH CA" },
	{ "LOS ANGELES CA" },
	{ "LOUISVILLE KY" },
	{ "LOWELL MA" },
	{ "LUANDA ANGOLA" },
	{ "LUBBOCK TX" },
	{ "MACON GA" },
	{ "MADISON WA" },
	{ "MADISON WI" },
	{ "MADRID SPAIN" },
	{ "MANCHESTER NH" },
	{ "MANILA PHILIPPINES" },
	{ "MCALLEN TX" },
	{ "MCKINNEY TX" },
	{ "MELBOURNE AUSTRALIA" },
	{ "MEMPHIS TN" },
	{ "MESA AZ" },
	{ "MESQUITE TX" },
	{ "MEXICO CITY MEXICO" },
	{ "MIAMI FL" },
	{ "MIAMI GARDENS FL" },
	{ "MIDLAND TX" },
	{ "MILAN ITALY" },
	{ "MILWAUKEE WA" },
	{ "MINNEAPOLIS MN" },
	{ "MIRAMAR FL" },
	{ "MOBILE AL" },
	{ "MODESTO CA" },
	{ "MONTERREY MEXICO" },
	{ "MONTGOMERY AL" },
	{ "MONTGOMERY WV" },
	{ "MORENO VALLEY CA" },
	{ "MUMBAI INDIA" },
	{ "MUNICH GERMANY" },
	{ "MURFREESBORO TN" },
	{ "MURRIETA CA" },
	{ "NAGOYA JAPAN" },
	{ "NANCHANG CHINA" },
	{ "NANJING CHINA" },
	{ "NAPERVILLE IL" },
	{ "NASHVILLE TN" },
	{ "NEW DELHI INDIA" },
	{ "NEW HAVEN CT" },
	{ "NEW ORLEANS LA" },
	{ "NEW ORLEANS LA" },
	{ "NEW YORK NY" },
	{ "NEWARK NJ" },
	{ "NEWPORT NEWS VA" },
	{ "NORFOLK VA" },
	{ "NORMAN OK" },
	{ "NORTH CHARLESTON SC" },
	{ "NORTH LAS VEGAS NV" },
	{ "NORWALK CA" },
	{ "OAKLAND CA" },
	{ "OCEANSIDE CA" },
	{ "ODESSA TX" },
	{ "OKLAHOMA CITY OK" },
	{ "OLATHE KS" },
	{ "OMAHA NE" },
	{ "ONTARIO CA" },
	{ "ORANGE CA" },
	{ "ORLANDO FL" },
	{ "OSAKA JAPAN" },
	{ "OVERLAND PARK KS" },
	{ "OXNARD CA" },
	{ "PALM BAY FL" },
	{ "PALMDALE CA" },
	{ "PARIS FRANCE" },
	{ "PASADENA CA" },
	{ "PASADENA TX" },
	{ "PATERSON NJ" },
	{ "PEARLAND TX" },
	{ "PEMBROKE PINES FL" },
	{ "PEORIA AZ" },
	{ "PEORIA IL" },
	{ "PHILADELPHIA PA" },
	{ "PHOENIX AZ" },
	{ "PITTSBURGH PA" },
	{ "PLANO TX" },
	{ "POMONA CA" },
	{ "POMPANO BEACH FL" },
	{ "PORT ST LUCIE FL" },
	{ "PORTLAND OR" },
	{ "PROVIDENCE RI" },
	{ "PROVO UT" },
	{ "PUEBLO CO" },
	{ "PUNE INDIA" },
	{ "QINGDAO CHINA" },
	{ "RALEIGH NC" },
	{ "RANCHO CUCAMONGA CA" },
	{ "RENO NV" },
	{ "RHINE RUHR GERMANY" },
	{ "RIALTO CA" },
	{ "RICHARDSON TX" },
	{ "RICHMOND CA" },
	{ "RICHMOND VA" },
	{ "RIO DE JANEIRO BR" },
	{ "RIVERSIDE CA" },
	{ "ROCHESTER MN" },
	{ "ROCHESTER NY" },
	{ "ROCKFORD IL" },
	{ "ROME ITALY" },
	{ "ROSEVILLE CA" },
	{ "ROUND ROCK TX" },
	{ "SACRAMENTO CA" },
	{ "SALEM OR" },
	{ "SALINAS CA" },
	{ "SALT LAKE CITY UT" },
	{ "SAN ANTONIO TX" },
	{ "SAN BERNARDINO CA" },
	{ "SAN DIEGO CA" },
	{ "SAN FRANCISCO CA" },
	{ "SAN JOSE CA" },
	{ "SAN MATEO CA" },
	{ "SANDY SPRINGS GA" },
	{ "SANTA ANA CA" },
	{ "SANTA CLARA CA" },
	{ "SANTA CLARITA CA" },
	{ "SANTA MARIA CA" },
	{ "SANTA ROSA CA" },
	{ "SANTIAGO CHILE" },
	{ "SAO PAULO BRAZIL" },
	{ "SAVANNAH GA" },
	{ "SCOTTSDALE AZ" },
	{ "SEATTLE WA" },
	{ "SEOUL SOUTH KOREA" },
	{ "SHANGHAI CHINA" },
	{ "SHENYANG CHINA" },
	{ "SHENZHEN CHINA" },
	{ "SHREVEPORT LA" },
	{ "SIMI VALLEY CA" },
	{ "SIOUX FALLS SD" },
	{ "SOUTH BEND IN" },
	{ "SPOKANE WA" },
	{ "SPRINGFIELD IL" },
	{ "SPRINGFIELD MA" },
	{ "SPRINGFIELD MO" },
	{ "ST LOUIS MO" },
	{ "ST PAUL MN" },
	{ "ST PETERSBURG FL" },
	{ "STAMFORD CT" },
	{ "STERLING HEIGHTS MI" },
	{ "STOCKTON CA" },
	{ "STUTTGART GERMANY" },
	{ "SUNNYVALE CA" },
	{ "SURAT INDIA" },
	{ "SURPRISE AZ" },
	{ "SYDNEY AUSTRALIA" },
	{ "SYRACUSE NY" },
	{ "TACOMA WA" },
	{ "TAIPEI TAIWAN" },
	{ "TALLAHASSEE FL" },
	{ "TAMPA FL" },
	{ "TEHRAN IRAN" },
	{ "TEMECULA CA" },
	{ "TEMPE AZ" },
	{ "THORNTON CO" },
	{ "THOUSAND OAKS CA" },
	{ "TIANJIN CHINA" },
	{ "TOKYO JAPAN" },
	{ "TOLEDO OH" },
	{ "TOPEKA KS" },
	{ "TORONTO CANADA" },
	{ "TORRANCE CA" },
	{ "TUCSON AZ" },
	{ "TULSA OK" },
	{ "TYLER TX" },
	{ "VALLEJO CA" },
	{ "VANCOUVER WA" },
	{ "VENTURA CA" },
	{ "VICTORVILLE CA" },
	{ "VIRGINIA BEACH VA" },
	{ "VISALIA CA" },
	{ "WACO TX" },
	{ "WARREN MI" },
	{ "WASHINGTON DC" },
	{ "WATERBURY CT" },
	{ "WENZHOU CHINA" },
	{ "WEST COVINA CA" },
	{ "WEST JORDAN UT" },
	{ "WEST PALM BEACH FL" },
	{ "WEST VALLEY CITY UT" },
	{ "WESTMINSTER CO" },
	{ "WICHITA FALLS TX" },
	{ "WICHITA KS" },
	{ "WILMINGTON NC" },
	{ "WINSTON NC" },
	{ "WINSTON–SALEM NC" },
	{ "WORCESTER MA" },
	{ "WUHAN CHINA" },
	{ "XIAN CHINA" },
	{ "YONKERS NY" },
	{ "ZHENGZHOU CHINA" }
};

// QSO parts

const BHMorse_QSOPart BHMorse::_QSOParts[] PROGMEM =
{
	{" TNX FER CALL"},		// FB1
	{" FB"},							// FB2
	{" FB OM"},						// FB3
	{" R R"},							// FB4
	{""},									// FB5
	{" DE "},							// DE
	{" = UR RST IS "},		// RST1
	{" = RST "},					// RST2
	{" = MY NAME IS "},		// Name1
	{" = NAME HR IS "},		// Name2
	{" = NAME IS "},			// Name3
	{" = NAME "},					// Name4
	{" = QTH IS "},				// QTH1
	{" = QTH "},					// QTH2
	{" = HW CPY? "},			// Bk2U1
	{" = BK TO U "},			// Bk2U2
	{" = "},							// Bk2U3
	{" K "},							// K1
	{" ("}								// K2 {KN}
};

// temporary buffer for building messages

char _tmpBuffer[BHMORSE_MESSAGE_BUFRSIZE];

//////////////////////////////////////////////////////////////////////////////
// Character map
//////////////////////////////////////////////////////////////////////////////

const BHMorse::charElement BHMorse::_charElemMap[] PROGMEM =
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

	int r = random(0, ARRAY_SIZE(_firstNames));

	BHMorse_FirstName buffer;
	memcpy_P(&buffer, &_firstNames[r], sizeof(buffer));
	strcpy(retV, buffer.d);
}

void BHMorse::getRandomCity(char* retV)
{
	// return a random city from the table in PROGMEM

	int r = random(0, ARRAY_SIZE(_cities));

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
	// populate a table with pointers to all of the characters
	// in the current range of enabled groups

	_numCharGroupPtrs = 0;

	for (int i = 0; i < ARRAY_SIZE(_charElemMap); i++)
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

		// see if it's a valid index into the character map

		if ((c2s >= 0) &&
				(c2s < ARRAY_SIZE(_charElemMap)))
		{
			_tempChar = getCharElement(c2s);
		}
	}
}

void BHMorse::loadNextChar()
{
	// load next random character to send in enabled difficulty groups

	int rndChar = random(0, _numCharGroupPtrs);
	_tmpBuffer[0] = _ptrsToCharsInGroupRange[rndChar] + BHMORSE_CHAR_ELEMENT_MAP_OFFSET;
	_tmpBuffer[1] = '\0';
	setMessage(_tmpBuffer);
}

void BHMorse::loadNextGroup()
{
	// load next group of random characters in enabled difficulty groups

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

	p = random(BHMorse_QSOPart_Row::FB1, BHMorse_QSOPart_Row::FB5 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	// RST

	p = random(BHMorse_QSOPart_Row::RST1, BHMorse_QSOPart_Row::RST2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	getRandomRST(bufr);
	strcat(_tmpBuffer, bufr);

	// Name

	p = random(BHMorse_QSOPart_Row::Name1, BHMorse_QSOPart_Row::Name4 + 1);
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

	p = random(BHMorse_QSOPart_Row::Bk2U1, BHMorse_QSOPart_Row::Bk2U3 + 1);
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

	_ptrsToCharsInGroupRange = new byte[ARRAY_SIZE(_charElemMap)];

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
	// this is "s" in the ARRL calculations

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
// message parameter setters
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
	// read user character speed

	BHMorse_Wpm tmpWpm;
	EEPROM.get(BHMORSE_EEPROM_ADDR_USERCHARSPEED, tmpWpm);
	setUserCharSpeed(tmpWpm);
}

void BHMorse::readHighestEnabledGroup()
{
	// read highest enabled group

	BHMorse_charElemMap_Group tmpGroup;
	EEPROM.get(BHMORSE_EEPROM_ADDR_HIGHESTENABLEDGROUP, tmpGroup);
	setHighestEnabledGroup(tmpGroup);
}

void BHMorse::readPitch()
{
	// read pitch

	BHMorse_Hz tmpHz;
	EEPROM.get(BHMORSE_EEPROM_ADDR_PITCH, tmpHz);
	setPitch(tmpHz, true);
}

void BHMorse::loadSettings()
{
	// read persistent settings from EEPROM

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
	// reset settings to factory defaults

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
	// returns true if any characters remain to be sent in the message

	return (_numCharsInMsgSent < strlen(_message));
}

boolean BHMorse::msgDone()
{
	// returns true if any elements remain to be sent in the current character,
	// or any characters remain to be sent in the message

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
	// [this requires the bit after the last used bit to still be 0]

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

			// only if the next char isn't a space, wait inter-character space,
			// so we don't add inter-char space to inter-word space

			if (!isSpace(_tempChar))
			{
				waitInterCharSpace();
			}
		}
		else
		{
			// message is finished
			// see if I need to load the next message

			switch (runMode())
			{
				case Idle:
					// weird; I shouldn't be here
					break;

				case SendMessage:
					// wait a little
					waitInterCharSpace();
					// go idle
					setRunMode(Idle);
					break;

				case SendChars:
					// wait a little
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
