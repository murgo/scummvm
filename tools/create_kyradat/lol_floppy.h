const ExtractEntry lolFloppyFile2G[] = {
	{ kLolIngamePakFiles, 0x0038C38, 0x0038CC0 },

	{ kLolCharacterDefs, 0x0002A6D0, 0x0002AB62 },
	{ kLolIngameSfxFiles, 0x0002ACA0, 0x0002B592 },
	{ kLolIngameSfxIndex, 0x0002B592, 0x0002B97A },
	{ kLolMusicTrackMap, 0x0002ABB0, 0x0002ACA0 },
	{ kLolGMSfxIndex, 0x0002B980, 0x0002BA7A },
	{ kLolMT32SfxIndex, 0x0002BA80, 0x0002BB7A },
	{ kLolSpellProperties, 0x0002C0E0, 0x0002C1F8 },
	{ kLolGameShapeMap, 0x0002BE5C, 0x0002BF70 },
	{ kLolSceneItemOffs, 0x0003730F, 0x00037317 },
	{ kLolCharInvIndex, 0x0002BF70, 0x0002BF7A },
	{ kLolCharInvDefs, 0x0002BF7A, 0x0002BFD2 },
	{ kLolCharDefsMan, 0x0002BFD2, 0x0002BFE4 },
	{ kLolCharDefsWoman, 0x0002BFE4, 0x0002BFF6 },
	{ kLolCharDefsKieran, 0x0002BFF6, 0x0002C008 },
	{ kLolCharDefsAkshel, 0x0002C01A, 0x0002C02C },
	{ kLolExpRequirements, 0x00031750, 0x0003177C },
	{ kLolMonsterModifiers, 0x0003177C, 0x00031794 },
	{ kLolMonsterLevelOffsets, 0x000372DF, 0x000372FF },
	{ kLolMonsterDirFlags, 0x000372FF, 0x0003730F },
	{ kLolMonsterScaleY, 0x00036EC0, 0x00036EDE },
	{ kLolMonsterScaleX, 0x00036EDE, 0x00036EFE },
	{ kLolMonsterScaleWH, 0x00028F30, 0x00028FB2 },
	{ kLolFlyingItemShp, 0x00028FB2, 0x00029034 },
	{ kLolInventoryDesc, 0x00037ACE, 0x00037AE4 },

	{ kLolLevelShpList, 0x00037C02, 0x00037C81 },
	{ kLolLevelDatList, 0x00037C81, 0x00037D00 },
	{ kLolCompassDefs, 0x00029034, 0x00029134 },
	{ kLolStashSetup, 0x0003781D, 0x00037829 },

	{ kLolDscUnk1, 0x00037317, 0x0003733B },
	{ kLolDscShapeIndex1, 0x0003733B, 0x0003735F },
	{ kLolDscShapeIndex2, 0x0003735F, 0x00037369 },
	{ kLolDscScaleWidthData, 0x00037369, 0x000373B1 },
	{ kLolDscScaleHeightData, 0x000373B1, 0x000373F9 },
	{ kLolDscX, 0x000373F9, 0x00037441 },
	{ kLolDscY, 0x00037441, 0x00037465 },
	{ kLolDscTileIndex, 0x00037465, 0x00037477 },
	{ kLolDscUnk2, 0x00037477, 0x0003748E },
	{ kLolDscDoorShapeIndex, 0x0003748E, 0x000374A5 },
	{ kLolDscDimData1, 0x00036F03, 0x00037047 },
	{ kLolDscDimData2, 0x00037047, 0x000372D0 },
	{ kLolDscBlockMap, 0x00036E64, 0x00036E70 },
	{ kLolDscDimMap, 0x00036E70, 0x00036E82 },
	{ kLolDscDoorScale, 0x00036E82, 0x00036E92 },
	{ kLolDscShapeOvlIndex, 0x00036E92, 0x00036EBA },
	{ kLolDscDoor4, 0x00036EBA, 0x00036EC2 },
	{ kLolDscBlockIndex, 0x00038B87, 0x00038BCF },
	{ kLolDscDoor1, 0x0002C050, 0x0002C0D0 },
	{ kLolDscDoorX, 0x00028630, 0x00028AB0 },
	{ kLolDscDoorY, 0x00028AB0, 0x00028F30 },

	{ kLolScrollXTop, 0x0003C216, 0x0003C220 },
	{ kLolScrollYTop, 0x0003C220, 0x0003C22A },
	{ kLolScrollXBottom, 0x0003C22A, 0x0003C234 },
	{ kLolScrollYBottom, 0x0003C234, 0x0003C23E },

	{ kLolButtonDefs, 0x000297F0, 0x0002A01A },
	{ kLolButtonList1, 0x0002A020, 0x0002A070 },
	{ kLolButtonList2, 0x0002A070, 0x0002A08E },
	{ kLolButtonList3, 0x0002A090, 0x0002A094 },
	{ kLolButtonList4, 0x0002A0A0, 0x0002A0BE },
	{ kLolButtonList5, 0x0002A0C0, 0x0002A0E0 },
	{ kLolButtonList6, 0x0002A0E0, 0x0002A0FC },
	{ kLolButtonList7, 0x0002A100, 0x0002A106 },
	{ kLolButtonList8, 0x0002A110, 0x0002A114 },

	{ kLolLegendData, 0x000374F0, 0x0003752C },
	{ kLolMapCursorOvl, 0x0003752C, 0x00037545 },
	{ kLolMapStringId, 0x00029140, 0x0002917C },

	{ kLolSpellbookAnim, 0x00038668, 0x000386A0 },
	{ kLolSpellbookCoords, 0x000386A0, 0x000386B8 },
	{ kLolHealShapeFrames, 0x0002A140, 0x0002A190 },
	{ kLolLightningDefs, 0x00037B08, 0x00037B1C },
	{ kLolFireballCoords, 0x0001E6E2, 0x0001E8E2 },

	{ -1, 0, 0 }
};

const Game lolDosFloppyGames[] = {
	{ kLol, EN_ANY, -1, "6b843869772c1b779e1386be868c15dd", lolFloppyFile2G },
	GAME_DUMMY_ENTRY
};
