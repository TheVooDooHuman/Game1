

int getCurrentMission(int x) 
{
	int mission = 0;
	if ((x > 0) && (x < 400)) { mission = 0; }
	if (x > 400){ mission = 1; }
	if (x > 700) { mission = 2; }
	if (x > 2200) { mission = 3; }
	return mission;
}

 std::string getTextMission(int currentMission)
{
	 std::string missionText = "";

	 switch (currentMission)
	 {
		 case 0: missionText = "\nНачальный этап\nИнструкция к игре"; break;
		 case 1: missionText = "\nMission 1\nПервая миссия\n"; break;
		 case 2: missionText = "\nMission 2\nВторая миссия\n"; break;
		 case 3: missionText = "\nMission 3\nТретья миссия\n"; break;
	 }

	 return  missionText;
}
