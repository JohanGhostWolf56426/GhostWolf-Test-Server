void SpawnObject(string objectName, vector position, vector orientation)
{
    Object obj;
    obj = Object.Cast(GetGame().CreateObject(objectName, "0 0 0"));
    obj.SetPosition(position);
    obj.SetOrientation(orientation);
    // Force update collisions
    if (obj.CanAffectPathgraph())
    {
        obj.SetAffectPathgraph(true, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
    }
}
void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	//Weather weather = g_Game.GetWeather();
	//weather.MissionWeather(false);    // false = use weather controller from Weather.c
	//weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	//weather.GetRain().Set( 0, 0, 1);
	//weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
  
    {
    
    	//GetCEApi().ExportProxyData("0 0 0", 100000);
		//GetCEApi().ExportClusterData();
  
    }

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 2, reset_day = 20;
	
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
	
    //CEApi TestHive = GetCEApi();
    //TestHive.ExportProxyProto();
    //TestHive.ExportProxyData( "8096 0 8096", 16384 );
    //TestHive.ExportClusterData() ;	  	
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {
    	player.RemoveAllItems();

    	EntityAI itemEnt;
    	ItemBase itemBs;

    	switch (Math.RandomInt(0, 3)) {
    	case 0:
    	// Freshy 0
        
    	player.GetInventory().CreateInInventory("A_CostCutter");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("JumpsuitPants_Grey");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("HikingBoots_Black");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_Guinness");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_MilkyWay");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("BoneKnife");itemBs = ItemBase.Cast(itemEnt);
    	break;
    	case 1:
    	// Freshy 1
        
    	player.GetInventory().CreateInInventory("A_MarmiteShirt");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("JumpsuitPants_Grey");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("HikingBoots_Black");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_Guinness");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_MilkyWay");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("BoneKnife");itemBs = ItemBase.Cast(itemEnt);
    	break;
    	case 2:
    	// Freshy 2
        
    	player.GetInventory().CreateInInventory("A_TescoShirt");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("JumpsuitPants_Grey");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("HikingBoots_Black");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_Guinness");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_MilkyWay");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("BoneKnife");itemBs = ItemBase.Cast(itemEnt);
    	break;
    	case 3:
    	// Freshy 3
        
    	player.GetInventory().CreateInInventory("A_NettoShirt");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("JumpsuitPants_Grey");itemBs = ItemBase.Cast(itemEnt);
    	player.GetInventory().CreateInInventory("HikingBoots_Black");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_Guinness");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("MFP_MilkyWay");itemBs = ItemBase.Cast(itemEnt);
        player.GetInventory().CreateInInventory("BoneKnife");itemBs = ItemBase.Cast(itemEnt);
    	break;

    									}
        //   Give universal gear
    	itemEnt = player.GetInventory().CreateInInventory("BandageDressing");
    	itemBs = ItemBase.Cast(itemEnt);
    	itemBs.SetQuantity(4);
        //		SetRandomHealth(itemEnt);
        //		player.GetInventory().CreateInInventory("BoneKnife");
    }
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}