//Spawn helper function
void SpawnObject( string type, vector position, vector orientation )
{
auto obj = GetGame().CreateObject( type, position );
obj.SetPosition( position );
obj.SetOrientation( orientation );
obj.SetOrientation( obj.GetOrientation() ); //Collision fix
obj.Update();
obj.SetAffectPathgraph( true, false );
if( obj.CanAffectPathgraph() ) GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, obj );
}

void main()
{
	/*
	  [Namalsk] CE init (offline)
	*/
	CreateHive();
	GetHive().InitOffline();

	// GIMMIE DA LOOT
    //GetCEApi().ExportProxyData( "7500 0 7500", 100000000 );

    Weather weather = GetGame().GetWeather();
	weather.SetStorm( 0, 1, 1 );


	/*
	  [Namalsk] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	   currently recommended time-frame is:
		8/1 -> 8/31
		keep in mind that gameplay features are tied to the mission date (stored in the storage) and that it SHOULD remain this period!
	   while using:
		day accelerated 6 times (serverTimeAcceleration=6), resulting in an average 78 min of day-time (RL)
		night accelerated 24 times (serverNightTimeAcceleration=4), resulting in an average of 26 min of night-time (RL)
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );

    if ( month < 12 )
    {
    	year = 2150;
        month = 8;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
};

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 1 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.75 );
			m_EventManagerServer.RegisterEvent( LXDTremors, 0.4 );
			m_EventManagerServer.RegisterEvent( LXDHeatWave, 0.3 );
			m_EventManagerServer.RegisterEvent( LXDDustStorm, 0.3 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.45 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.2 );
		}
	}

	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat( 0.50, 0.85 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
		
		// top
		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" );
			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				SetRandomHealth( itemEnt );
				itemBs.SetQuantity( 3 );
				itemBs.SetCleanness( 1 );
			}
			player.SetQuickBarEntityShortcut( itemEnt, 0 );
		}

		// pants
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
		{
			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			int rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			SetRandomHealth( itemEnt );

			rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			if ( rand < 0.35 )
				itemEnt = player.GetInventory().CreateInInventory( "Apple" );
			else if ( rand > 0.65 )
				itemEnt = player.GetInventory().CreateInInventory( "Pear" );
			else
				itemEnt = player.GetInventory().CreateInInventory( "Orange" );

			SetRandomHealth( itemEnt );
		}

		// shoes
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
		}
	}
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
};
