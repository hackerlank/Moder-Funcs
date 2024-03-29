#pragma once

#define SF_SAMP

enum DialogStyle
{
	DIALOG_STYLE_MSGBOX,
	DIALOG_STYLE_INPUT,
	DIALOG_STYLE_LIST,
	DIALOG_STYLE_PASSWORD,
};
enum Gamestate
{
	GAMESTATE_NONE			= 0,
	GAMESTATE_WAIT_CONNECT	= 9,
	GAMESTATE_DISCONNECTED	= 13,
	GAMESTATE_AWAIT_JOIN	= 15,
	GAMESTATE_CONNECTED		= 14,
	GAMESTATE_RESTARTING	= 18
};
enum PlayerState
{
	PLAYER_STATE_NONE		= 0,
	PLAYER_STATE_ONFOOT		= 17,
	PLAYER_STATE_PASSENGER,
	PLAYER_STATE_DRIVER,
	PLAYER_STATE_WASTED		= 32,
	PLAYER_STATE_SPAWNED
};
enum Limits
{
	SAMP_MAX_ACTORS			= 1000,
	SAMP_MAX_PLAYERS		= 1004,
	SAMP_MAX_VEHICLES		= 2000,
	SAMP_MAX_PICKUPS		= 4096,
	SAMP_MAX_OBJECTS		= 1000,
	SAMP_MAX_GANGZONES		= 1024,
	SAMP_MAX_3DTEXTS		= 2048,
	SAMP_MAX_TEXTDRAWS		= 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS		= 144,
	SAMP_MAX_MENUS			= 128,
	SAMP_MAX_PLAYER_NAME	= 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
};
enum ChatMessageType
{
	CHAT_TYPE_NONE				= 0,
	CHAT_TYPE_CHAT				= 2,
	CHAT_TYPE_INFO				= 4,
	CHAT_TYPE_DEBUG				= 8
};

enum ChatDisplayMode
{
	CHAT_WINDOW_MODE_OFF		= 0,
	CHAT_WINDOW_MODE_LIGHT		= 1,
	CHAT_WINDOW_MODE_FULL		= 2
};

enum eSendrateType
{
	ONFOOTSENDRATE			= 1,
	INCARSENDRATE,
	AIMSENDRATE
};

typedef enum detour_types_s
{
	DETOUR_TYPE_NOT_SET		= -1,
	DETOUR_TYPE_JMP,
	DETOUR_TYPE_PUSH_RET,
	DETOUR_TYPE_PUSH_FUNC,
	DETOUR_TYPE_CALL_FUNC,
} detour_types_t;

#pragma pack( push, 1 )

// structures
struct stSAMPPools
{
	struct stActorPool		*pActor;
	struct stObjectPool		*pObject;
	struct stGangzonePool	*pGangzone;
	struct stTextLabelPool	*pText3D;
	struct stTextdrawPool	*pTextdraw;
	void					*pPlayerLabels;
	struct stPlayerPool		*pPlayer;
	struct stVehiclePool	*pVehicle;
	struct stPickupPool		*pPickup;
};

struct API stSAMP
{
	void					*pUnk0[2];
	uint8_t					byteSpace[24];
	char					szIP[257];
	char					szHostname[259];
	uint8_t					byteUnk1;
	uint32_t				ulPort;
	uint32_t				ulMapIcons[100];
	int						iLanMode;
	int						iGameState;
	uint32_t				ulConnectTick;
	struct stServerPresets	*pSettings;
	void					*pRakClientInterface;
	struct stSAMPPools		*pPools;

	// functions
	void					RestartGame( void );
	short					GetAnimationIDFromName( char *pszAnimFile, char *pszAnimName );
	char					*GetAnimationNameFromID( short sAnimationID );
	void					UpdateScoreAndPing( void );
	RPCNode					*GetRPCNodeByIndex( uint8_t index );
};

struct stServerPresets
{
	uint8_t byteCJWalk;
	uint8_t byteUnk0[4];
	float	fWorldBoundaries[4];
	uint8_t byteUnk1;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint32_t ulVehicleFriendlyFire;
	uint8_t byteUnk2[4];
	int		iClassesAvailable;
	float	fNameTagsDistance;
	uint8_t byteUnk3;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t byteNoNametagsBehindWalls;
	uint8_t bytePlayerMarkersMode;
	uint8_t byteUnk4[3];
	float	fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
};

struct stTextDrawTransmit
{
	union
	{
		BYTE byteFlags;
		struct
		{
			BYTE byteBox : 1;
			BYTE byteLeft : 1;
			BYTE byteRight : 1;
			BYTE byteCenter : 1;
			BYTE byteProportional : 1;
			BYTE bytePadding : 3;
		};
	};
	float fLetterWidth;
	float fLetterHeight;
	DWORD dwLetterColor;
	float fBoxWidth;
	float fBoxHeight;
	DWORD dwBoxColor;
	BYTE byteShadow;
	BYTE byteOutline;
	DWORD dwBackgroundColor;
	BYTE byteStyle;
	BYTE byteUNK;
	float fX;
	float fY;
	uint16_t sModel;
	float fRot[3];
	float fZoom;
	WORD sColor[2];
};

struct stTextdraw
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct API stTextdrawPool
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw	*textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw	*playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];

	stTextdraw *Create( uint16_t id, stTextDrawTransmit *transmit, char *text );
	void Delete( uint16_t id );
	bool IsExists( uint16_t id );
	bool GetTransmit( uint16_t id, stTextDrawTransmit &transmit );
	struct stTextdraw *GetTextdraw( uint16_t id );
};

struct stPickup
{
	int		iModelID;
	int		iType;
	float	fPosition[3];
};

struct API stPickupPool
{
	int				iPickupsCount;
	uint32_t		ul_GTA_PickupID[SAMP_MAX_PICKUPS];
	int				iPickupID[SAMP_MAX_PICKUPS];
	int				iTimePickup[SAMP_MAX_PICKUPS];
	uint8_t			unk[SAMP_MAX_PICKUPS * 3];
	struct stPickup pickup[SAMP_MAX_PICKUPS];

	// functions
	DWORD			GetPickupHandleByID( int iID );
	int				GetPickupIDByHandle( DWORD dwHandle );
	bool			IsPickupExists( int iID );
};

struct API stPlayerPool
{
	uint32_t				ulUnk0;
	uint16_t				sLocalPlayerID;
	void					*pVTBL_txtHandler;
	union
	{
		char	szLocalPlayerName[16];
		char	*pszLocalPlayerName;
	};
	int						iLocalPlayerNameLen;
	int						iLocalPlayerNameAllocated;
	struct stLocalPlayer	*pLocalPlayer;
	int						iLocalPlayerPing;
	int						iLocalPlayerScore;
	struct stRemotePlayer	*pRemotePlayer[SAMP_MAX_PLAYERS];
	int						iIsListed[SAMP_MAX_PLAYERS];
	uint32_t				ulUnk1[SAMP_MAX_PLAYERS];

	// functions
	int						SetLocalPlayerName( const char *name );
	int						GetSAMPPlayerIDFromGTAHandle( uint32_t GTA_Ped_ID );
	int						GetActorHandleFromSAMPPlayerID( int playerId );
	const char				*GetPlayerName( int iPlayerID );
	DWORD					GetPlayerColor( int id );
	short					GetPlayerAnimation( int iPlayerID );
	bool					IsPlayerDefined( int playerId, bool check_streamed = false );
	struct stOnFootData		*GetOnFootData( int playerId );
	struct stInCarData		*GetInCarData( int playerId );
	struct stPassengerData	*GetPassengerData( int playerId );
	struct stAimData		*GetAimData( int playerId );
	struct stTrailerData	*GetTrailerData( int playerId );
};

struct stSAMPKeys
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stOnFootData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	short		sCurrentAnimationID;
	short		sAnimFlags;
};

struct stInCarData
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
	};
};

struct stAimData
{
	BYTE	byteCamMode;
	float	vecAimf1[3];
	float	vecAimPos[3];
	float	fAimZ;
	BYTE	byteCamExtZoom : 6;		// 0-63 normalized
	BYTE	byteWeaponState : 2;	// see eWeaponState
	BYTE	bUnk;
};

struct stTrailerData
{
	uint16_t	sTrailerID;
	float		fPosition[3];
	//float		fRoll[3];
	//float		fDirection[3];
	float		fQuaternion[4]; // not tested
	float		fSpeed[3];
	float		fUnk[2];
	uint32_t	pad;
};

struct stPassengerData
{
	uint16_t	sVehicleID;
	uint8_t		byteSeatID;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

struct stDamageData
{
	uint16_t	sVehicleID_lastDamageProcessed;
	int			iBumperDamage;
	int			iDoorDamage;
	uint8_t		byteLightDamage;
	uint8_t		byteWheelDamage;
};

struct stSurfData
{
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnk0;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	struct stSAMPVehicle *pSurfingVehicle;
	int			iUnk1;
	int			iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};


struct stUnoccupiedData
{
	int16_t sVehicleID;
	uint8_t byteSeatID;
	float	fRoll[3];
	float	fDirection[3];
	float	fPosition[3];
	float	fMoveSpeed[3];
	float	fTurnSpeed[3];
	float	fHealth;
};

struct stBulletData
{
	uint8_t		byteType;
	uint16_t	sTargetID;
	float		fOrigin[3];
	float		fTarget[3];
	float		fCenter[3];
	uint8_t		byteWeaponID;
};

struct stSpectatorData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

struct stStatsData
{
	int iMoney;
	int iAmmo;	// ?
};

struct stHeadSync
{
	float	fHeadSync[3];
	int		iHeadSyncUpdateTick;
	int		iHeadSyncLookTick;
};

struct API stLocalPlayer
{
	struct stSAMPPed		*pSAMP_Actor;
	uint16_t				sCurrentAnimID;
	uint16_t				sAnimFlags;
	uint32_t				ulUnk0;
	int						iIsActive;
	int						iIsWasted;
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	struct stOnFootData		onFootData;
	struct stPassengerData	passengerData;
	struct stTrailerData	trailerData;
	struct stInCarData		inCarData;
	struct stAimData		aimData;
	uint8_t					byteTeamID;
	int						iSpawnSkin;
	uint8_t					byteUnk1;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID2;
	uint16_t				usUnk2;
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint16_t				sAimingAtPid;
	uint16_t				usUnk3;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	uint16_t				sTargetObjectID;
	uint16_t				sTargetVehicleID;
	uint16_t				sTargetPlayerID;
	struct stHeadSync		headSyncData;
	uint32_t				ulHeadSyncTick;
	BYTE					byteSpace3[260];
	struct stSurfData		surfData;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	uint32_t				ulUnk4;
	uint8_t					byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t					byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int						iSpectateID;
	int						iInitiatedSpectating;
	struct stDamageData		vehicleDamageData;

	// functions
	void					Spawn( void );
	void					SendDeath( void );
	void					SetSpecialAction( uint8_t byteSpecialAction );
	void					RequestClass( int ClassId );
	void					Say( char *msg );
	void					SendEnterVehicle( int vehicleId, int passenger );
	void					SendExitVehicle( int vehicleId );
};

struct stRemotePlayerData
{
	struct stSAMPPed		*pSAMP_Actor;
	struct stSAMPVehicle	*pSAMP_Vehicle;
	uint8_t					byteTeamID;
	uint8_t					bytePlayerState;
	uint8_t					byteSeatID;
	uint32_t				ulUnk3;
	int						iPassengerDriveBy;
	void					*pUnk0;
	uint8_t					byteUnk1[60];
	float					fSomething[3];
	float					fVehicleRoll[4];
	uint32_t				ulUnk2[3];
	float					fOnFootPos[3];
	float					fOnFootMoveSpeed[3];
	float					fVehiclePosition[3];
	float					fVehicleMoveSpeed[3];
	uint16_t				sPlayerID;
	uint16_t				sVehicleID;
	uint32_t				ulUnk5;
	uint8_t					byteUnk6[2];
	short					sShowNameTag;
	int						iHasJetPack;
	uint8_t					byteSpecialAction;
	uint32_t				ulUnk4[3];
	struct stOnFootData		onFootData;
	struct stInCarData		inCarData;
	struct stTrailerData	trailerData;
	struct stPassengerData	passengerData;
	struct stAimData		aimData;
	float					fActorArmor;
	float					fActorHealth;
	uint32_t				ulUnk10;
	uint8_t					byteUnk9;
	uint32_t				dwTick;
	uint32_t				dwLastStreamedInTick;	// is 0 when currently streamed in
	uint32_t				ulUnk7;
	int						iAFKState;
	struct stHeadSync		headSyncData;
	int						iGlobalMarkerLoaded;
	int						iGlobalMarkerLocation[3];
	uint32_t				ulGlobalMarker_GTAID;
};

struct stStreamedOutPlayerInfo
{
	float	fPlayerPos[SAMP_MAX_PLAYERS][3];
};

struct stRemotePlayer
{
	stRemotePlayerData	*pPlayerData;
	int					iIsNPC;
	void				*pVTBL_txtHandler;
	union
	{
		char			szPlayerName[16];
		char			*pszPlayerName;
	};
	int					iNameLen;
	int					iNameAllocated;
	int					iScore;
	int					iPing;
};

template <typename T>
struct stSAMPEntity
{
	void		*pVTBL;
	uint8_t		byteUnk0[60]; // game CEntity object maybe. always empty.
	T			*pGTAEntity;
	uint32_t	ulGTAEntityHandle;
};

struct stSAMPPed : public stSAMPEntity < struct actor_info >
{
	int					usingCellPhone;
	uint8_t				byteUnk0[600];
	struct actor_info	*pGTA_Ped;
	uint8_t				byteUnk1[22];
	uint8_t				byteKeysId;
	uint16_t			ulGTA_UrinateParticle_ID;
	int					DrinkingOrSmoking;
	int					object_in_hand;
	int					drunkLevel;
	uint8_t				byteUnk2[5];
	int					isDancing;
	int					danceStyle;
	int					danceMove;
	uint8_t				byteUnk3[20];
	int					isUrinating;
};

struct API stVehiclePool
{
	int						iVehicleCount;
	void					*pUnk0;
	uint8_t					byteSpace1[0x112C];
	struct stSAMPVehicle	*pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	struct vehicle_info		*pGTA_Vehicle[SAMP_MAX_VEHICLES];
	uint8_t					byteSpace2[SAMP_MAX_VEHICLES * 6];
	uint32_t				ulShit[SAMP_MAX_VEHICLES];
	int						iIsListed2[SAMP_MAX_VEHICLES];
	uint32_t				byteSpace3[SAMP_MAX_VEHICLES * 2];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated;

	// functions
	int						GetSAMPVehicleIDFromGTAHandle( uint32_t GTA_Vehicle_ID );
	int						GetCarHandleFromSAMPCarID( int vehicleId );
};

struct stSAMPVehicle : public stSAMPEntity < vehicle_info >
{
	uint32_t			bUnk0;
	struct vehicle_info *pGTA_Vehicle;
	uint8_t				byteUnk1[8];
	int					bIsMotorOn;
	int					iIsLightsOn;
	int					iIsLocked;
	uint8_t				byteIsObjective;
	int					iObjectiveBlipCreated;
	uint8_t				byteUnk2[20];
	uint8_t				byteColor[2];
	int					iColorSync;
	int					iColor_something;
};

struct stObject : public stSAMPEntity < struct object_info >
{
	uint8_t				byteUnk0[2];
	uint32_t			ulUnk1;
	int					iModel;
	uint8_t				byteUnk2;
	float				fDrawDistance;
	float				fUnk;
	float				fPos[3];
	// ...
};

struct API stObjectPool
{
	int				iObjectCount;
	int				iIsListed[SAMP_MAX_OBJECTS];
	struct stObject *object[SAMP_MAX_OBJECTS];

	// functions
	DWORD			GetObjectHandleByID( int iID );
	int				GetObjectIDByHandle( DWORD dwHandle );
	bool			IsObjectExists( int iID );
};

struct stGangzone
{
	float	fPosition[4];
	DWORD	dwColor;
	DWORD	dwAltColor;
};

struct stGangzonePool
{
	struct stGangzone	*pGangzone[SAMP_MAX_GANGZONES];
	int					iIsListed[SAMP_MAX_GANGZONES];
};

struct stTextLabel
{
	char		*pText;
	DWORD		color;
	float		fPosition[3];
	float		fMaxViewDistance;
	uint8_t		byteShowBehindWalls;
	uint16_t	sAttachedToPlayerID;
	uint16_t	sAttachedToVehicleID;
};

struct API stTextLabelPool
{
	struct stTextLabel	textLabel[SAMP_MAX_3DTEXTS];
	int					iIsListed[SAMP_MAX_3DTEXTS];

	// functions
	int					Create3DText( uint16_t id, char *szText, D3DCOLOR Color, float fPosition[3], float fViewDistance,
		bool bShowBehindWalls, USHORT sAttachedToPlayer, USHORT sAttachedToVehicle );
	int					Create3DText( char *szText, D3DCOLOR Color, float fPosition[3], float fViewDistance,
		bool bShowBehindWalls, USHORT sAttachedToPlayer, USHORT sAttachedToVehicle );
	int					Create3DText( uint16_t id, stTextLabel textLabel );
	bool				Get3DTextInfo( uint16_t id, stTextLabel &textLabel );
	bool				Destroy3DText( int ID );
};

struct stChatEntry
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct stFontRenderer			//size = 0x20
{
	ID3DXFont	*m_pChatFont;
	ID3DXFont	*m_pLittleFont;
	ID3DXFont	*m_pChatShadowFont;
	ID3DXFont	*m_pLittleShadowFont;
	ID3DXFont	*m_pCarNumberFont;
	ID3DXSprite *m_pTempSprite;
	int			field_18;
	char		*m_pszTextBuffer;
};

struct API stChatInfo
{
	int					pagesize;
	void				*pUnk;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			iUnk;
	char				logFilePathChatLog[MAX_PATH + 1];
	void				*pGameUI; // CDXUTDialog
	void				*pEditBackground; // CDXUTEditBox
	void				*pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				dwChatboxOffset;
	struct stChatEntry	chatEntry[100];
	stFontRenderer		*m_pFontRenderer;
	ID3DXSprite			*m_pChatTextSprite;
	ID3DXSprite			*m_pSprite;
	IDirect3DDevice9	*m_pD3DDevice;
	int					field_63B2;
	DWORD				field_63B6;
	IDirect3DTexture9	*m_pTexture;
	int					field_63BE;
	int					field_63C2;
	int					field_63C6;
	int					field_63CA;
	int					field_63CE;
	int					field_63D2;
	int					field_63D6;
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iDistanceAfterTimestamp;
	int					field_63E6;

	// functions
	void				AddChatMessage( DWORD Color, const char *Text, ... );
	void				AddChatMessage( ChatMessageType Type, const char *szString, const char *szPrefix, D3DCOLOR TextColor,
		D3DCOLOR PrefixColor );
	void				SetDisplayMode( int mode );
};

typedef void ( __cdecl *CMDPROC ) ( PCHAR );
struct API stInputInfo
{
	void				*pD3DDevice;
	void				*pDXUTDialog;
	class _CDXUTEditBox *pDXUTEditBox;
	CMDPROC				pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC				pszDefaultCMD;

	// functions
	void				AddClientCommand( char *Command, DWORD Function );
	void				EnableInput( void );
	void				DisableInput( void );
};

struct stKillEntry
{
	char		szKiller[25];
	char		szVictim[25];
	D3DCOLOR	clKillerColor;
	D3DCOLOR	clVictimColor;
	uint8_t		byteType;
};

struct stKillInfo
{
	int					iEnabled;
	struct stKillEntry	killEntry[5];
	int					iXOffset[2];
	int					iYSpacing;
	// not tested
	ID3DXFont		    *pD3DFont;
	ID3DXFont			*pWeaponFont;
	ID3DXSprite			*pSprite;
	IDirect3DDevice9	*pD3DDevice;
	// ...
};

struct API stDialogInfo
{
	void				*pVTBL;
	int					iTextPoxX;
	int					iTextPoxY;
	int					iTextSizeX;
	int					iTextSizeY;
	int					iBtnOffsetX;
	int					iBtnOffsetY;
	class _CDXUTDialog	*pDialog;
	class _CDXUTListBox *pList;
	class _CDXUTEditBox *pEditBox;
	int					iIsActive;
	int					iType;
	DWORD				DialogID;
	char				*pText;
	DWORD				font;
	DWORD				font2;
	char				szCaption[64];
	byte				byteUnknown;
	int					bServerside;

	// functions
	void				Close( int iPressedBtn );
	void				ListBoxSetIndex( int iIndex );
	int					ListBoxGetIndex( void );
	int					ListBoxGetItemsCount( void );
	char				*ListBoxGetItemText( int id );
	wchar_t				*GetInputText( void );
	void				SetInputText( char *pwszText );
	void				ShowDialog( WORD wDialogId, int iStyle, char *szCaption, char *szInfo, char *szButton1,
		char *szButton2 );
};

struct stChatPlayer
{
	int		iCreated;
	char	probablyTheText[256];	// text max length = 144
	DWORD	dwTickCreated;
	DWORD	dwLiveLength;
	DWORD	dwColor;
	float	fDrawDistance;
	DWORD	dwUnknown;
};

struct API stMiscInfo	// sizeof = 321
{
	void	*pUnk0[3];
	uint8_t	byteSpace1[73];
	int		iCursorMode;
	int		iSomething[5];

	// byte	bytePad[228];
	void	ToggleCursor( bool bToggle );
	void	ToggleCursor( int mode, bool toggle );
};

struct API stScoreboardInfo
{
	int					iIsEnabled;
	int					iPlayersCount;
	float				fTextOffsetX;
	float				fTextOffsetY;
	float				fScalar;
	IDirect3DDevice9	*pDirectDevice;
	class _CDXUTDialog	*pDialog;
	class _CDXUTListBox *pList;
	int					iOffset;		// ?
	int					iIsSorted;		// ?

	// functions
	void				Enable( bool enable );
};

struct stActorPool
{
	int					iLastActorID;
	stSAMPEntity<void>	*pActor[SAMP_MAX_ACTORS]; // ?
	int					iIsListed[SAMP_MAX_ACTORS];
	struct actor_info	*pGTAPed[SAMP_MAX_ACTORS];
	uint32_t			ulUnk0[SAMP_MAX_ACTORS];
	uint32_t			ulUnk1[SAMP_MAX_ACTORS];
};

struct stChatBubbleInfo
{
	struct stChatPlayer chatBubble[SAMP_MAX_PLAYERS];
};

#pragma pack( pop )

class API SFSAMP
{
	SFPluginInfo* m_PluginInfo;
public:
	typedef void ( __stdcall *dialogCallback_t )( int dialogId, int buttonId, int listItem, const char *input );

	SFSAMP( SFPluginInfo* pluginInfo );
	SFPluginInfo* getPluginInfo( void );

	bool					IsInitialized( void );
	DWORD					getSAMPAddr( void );

	struct stSAMP			*getInfo( void );
	struct stPlayerPool		*getPlayers( void );
	struct stVehiclePool	*getVehicles( void );
	struct stChatInfo		*getChat( void );
	struct stInputInfo		*getInput( void );
	struct stKillInfo		*getDeathList( void );
	struct stDialogInfo		*getDialog( void );
	struct stMiscInfo		*getMisc( void );
	struct stScoreboardInfo *getScoreboard( void );
	struct stStreamedOutPlayerInfo *getStreamedOutInfo( void );		

	bool					registerChatCommand( std::string command, CommandProc callback );
	bool					registerDialogCallback( dialogCallback_t callback );
	void					disconnect( int Reason );
	void					requestClass( int ClassId );
	void					sendSCMEvent( int vehicleId, int iEvent, int iParam1, int iParam2 );
	void					sendEnterVehicle( int vehicleId, int passenger );
	void					sendExitVehicle( int vehicleId );
	void					sendSpawn( void );
	void					sendWastedNotification( byte reason, uint16_t playerId );
	void					sendRCONCommand( char *pszCommand );			
	void					sendDamageVehicle( WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires );
	void					sendClickPlayer( uint16_t playerId, byte source );
	void					sendDialogResponse( uint16_t dialogId, byte button, uint16_t listItem, char *pszInput );
	void					sendClickTextDraw( uint16_t textDrawId );
	void					sendGiveDamage( uint16_t targetId, float damage, int weapon, int bodypart );
	void					sendTakeDamage( uint16_t issuerId, float damage, int weapon, int bodypart );
	void					sendEditObject( bool playerObject, uint16_t objectId, int response, float pos_x, float pos_y,
		float pos_z, float rot_x, float rot_y, float rot_z );
	void					sendEditAttachedObject( int response, int id, int model, int bone, float offset_x,
		float offset_y, float offset_z, float rot_x, float rot_y,
		float rot_z, float scale_x, float scale_y, float scale_z );
	void					sendInteriorChange( byte interiorId );
	void					sendRequestSpawn( void );
	void					sendPickedUpPickup( int pickup );
	void					sendMenuSelect( byte row );
	void					sendMenuQuit( void );
	void					sendVehicleDestroyed( uint16_t vehicleId );
	void					setSendRate( eSendrateType eType, int iValue );
	void					takeScreenShot( void );
};