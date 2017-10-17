#include "global.h"
#include "battle.h"
#include "pokemon.h"
#include "battle_interface.h"
#include "sprite.h"
#include "window.h"
#include "string_util.h"
#include "text.h"

extern bool8 IsDoubleBattle(void);
extern u8 gBanksByIdentity[BATTLE_BANKS_COUNT];

// this file's functions
void sub_8072924(struct Sprite *sprite);
void sub_80728B4(struct Sprite *sprite);
const u32 *GetHealthboxElementGfxPtr(u8 elementId);
u32 AddTextPrinterAndCreateWindowOnHealthbox(u8 *str, u32 x, u32 y, u32 arg3, u32 *windowId);
void sub_8075198(void *objVram, u32 windowTileData, u32 arg2);
void RemoveWindow_(u32 windowId);
void sub_8075170(void *dest, u32 arg1, u32 arg2);
void UpdateHpTextInHealthboxInDoubles(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent);
void sub_807513C(void *dest, u32 arg1, u32 arg2);

// const rom data
const struct OamData gUnknown_0832C138 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

extern const struct SubspriteTable gUnknown_0832C28C[2];

static const struct SpriteTemplate gUnknown_0832C140[2] =
{
    {
        .tileTag = 0xD6FF,
        .paletteTag = 0xD6FF,
        .oam = &gUnknown_0832C138,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = 0xd700,
        .paletteTag = 0xD6FF,
        .oam = &gUnknown_0832C138,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }
};

static const struct SpriteTemplate gUnknown_0832C170[2] =
{
    {
        .tileTag = 0xd701,
        .paletteTag = 0xD6FF,
        .oam = &gUnknown_0832C138,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    },
    {
        .tileTag = 0xd702,
        .paletteTag = 0xD6FF,
        .oam = &gUnknown_0832C138,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallbackDummy
    }
};

static const struct SpriteTemplate gUnknown_0832C1A0 =
{
    .tileTag = 0xd70b,
    .paletteTag = 0xd6ff,
    .oam = &gUnknown_0832C138,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

const struct OamData gUnknown_0832C1B8 =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = 0,
    .matrixNum = 0,
    .size = 1,
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate gUnknown_0832C1C0[4] =
{
    {
        .tileTag = 0xd704,
        .paletteTag = 0xd704,
        .oam = &gUnknown_0832C1B8,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = sub_80728B4
    },
    {
        .tileTag = 0xd705,
        .paletteTag = 0xd704,
        .oam = &gUnknown_0832C1B8,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = sub_80728B4
    },
    {
        .tileTag = 0xd706,
        .paletteTag = 0xd704,
        .oam = &gUnknown_0832C1B8,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = sub_80728B4
    },
    {
        .tileTag = 0xd707,
        .paletteTag = 0xd704,
        .oam = &gUnknown_0832C1B8,
        .anims = gDummySpriteAnimTable,
        .images = NULL,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = sub_80728B4
    }
};

extern const u8 gUnknown_0832C3C4[0x14];
extern const u8 gUnknown_0832C3D8[0x14];

u8 sub_8072304(void)
{
    return 9;
}

#ifdef NONMATCHING
void sub_8072308(s16 arg0, u16 *arg1, u8 arg2)
{
    s8 i, j;
    s8 array[4];

    for (i = 0; i < 4; i++)
        array[i] = 0;

    i = 3;
    while (1)
    {
        if (arg0 < 0)
            break;

        array[i] = arg0 % 10;
        arg0 /= 10;
        i--;
    }

    for (j = i; j > -1; j--)
    {
        array[j] = -1;
    }

    if (array[3] == -1)
        array[3] = 0;

    if (arg2 == 0)
    {
        for (i = 0; i < 4; i++)
        {
            if (array[i] == -1)
            {
                arg1[i] &= 0xFC00;
                arg1[i] |= 0x1E;

                arg1[i + 0x20] &= 0xFC00;
                arg1[i + 0x20] |= 0x1E;
            }
            else
            {
                arg1[i] &= 0xFC00;
                arg1[i] |= array[i] + 0x14;

                arg1[i + 0x20] &= 0xFC00;
                arg1[i + 0x20] |= array[i] + 0x34;
            }
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            if (array[i] == -1)
            {
                arg1[i] &= 0xFC00;
                arg1[i] |= 0x1E;

                arg1[i + 0x20] &= 0xFC00;
                arg1[i + 0x20] |= 0x1E;
            }
            else
            {
                arg1[i] &= 0xFC00;
                arg1[i] |= array[i] + 0x14;

                arg1[i + 0x20] &= 0xFC00;
                arg1[i + 0x20] |= array[i] + 0x34;
            }
        }
    }
}

#else
__attribute__((naked))
void sub_8072308(s16 arg0, u16 *arg1, u8 arg2)
{
    asm(".syntax unified\n\
        	push {r4-r7,lr}\n\
	mov r7, r10\n\
	mov r6, r9\n\
	mov r5, r8\n\
	push {r5-r7}\n\
	sub sp, 0x4\n\
	adds r7, r1, 0\n\
	lsls r0, 16\n\
	lsrs r5, r0, 16\n\
	lsls r2, 24\n\
	lsrs r2, 24\n\
	mov r10, r2\n\
	movs r3, 0\n\
	movs r2, 0\n\
_08072324:\n\
	lsls r0, r3, 24\n\
	asrs r0, 24\n\
	mov r3, sp\n\
	adds r1, r3, r0\n\
	strb r2, [r1]\n\
	adds r0, 0x1\n\
	lsls r0, 24\n\
	lsrs r3, r0, 24\n\
	asrs r0, 24\n\
	cmp r0, 0x3\n\
	ble _08072324\n\
	movs r3, 0x3\n\
	movs r0, 0x1\n\
	negs r0, r0\n\
	mov r9, r0\n\
	mov r8, sp\n\
_08072344:\n\
	lsls r0, r5, 16\n\
	asrs r6, r0, 16\n\
	cmp r6, 0\n\
	ble _08072372\n\
	lsls r4, r3, 24\n\
	asrs r4, 24\n\
	mov r1, sp\n\
	adds r5, r1, r4\n\
	adds r0, r6, 0\n\
	movs r1, 0xA\n\
	bl __modsi3\n\
	strb r0, [r5]\n\
	adds r0, r6, 0\n\
	movs r1, 0xA\n\
	bl __divsi3\n\
	lsls r0, 16\n\
	lsrs r5, r0, 16\n\
	subs r4, 0x1\n\
	lsls r4, 24\n\
	lsrs r3, r4, 24\n\
	b _08072344\n\
_08072372:\n\
	lsls r1, r3, 24\n\
	asrs r0, r1, 24\n\
	cmp r0, r9\n\
	ble _08072396\n\
	movs r4, 0xFF\n\
	movs r3, 0x1\n\
	negs r3, r3\n\
_08072380:\n\
	asrs r2, r1, 24\n\
	mov r5, sp\n\
	adds r1, r5, r2\n\
	ldrb r0, [r1]\n\
	orrs r0, r4\n\
	strb r0, [r1]\n\
	subs r2, 0x1\n\
	lsls r1, r2, 24\n\
	asrs r0, r1, 24\n\
	cmp r0, r3\n\
	bgt _08072380\n\
_08072396:\n\
	mov r1, r8\n\
	ldrb r0, [r1, 0x3]\n\
	cmp r0, 0xFF\n\
	bne _080723A2\n\
	movs r0, 0\n\
	strb r0, [r1, 0x3]\n\
_080723A2:\n\
	mov r2, r10\n\
	cmp r2, 0\n\
	bne _08072432\n\
	movs r3, 0\n\
	movs r1, 0\n\
	movs r6, 0xFC\n\
	lsls r6, 8\n\
	movs r5, 0x1E\n\
	mov r12, r5\n\
_080723B4:\n\
	lsls r1, 24\n\
	asrs r2, r1, 24\n\
	mov r0, sp\n\
	adds r5, r0, r2\n\
	ldrb r0, [r5]\n\
	mov r8, r1\n\
	cmp r0, 0xFF\n\
	bne _080723EA\n\
	lsls r1, r2, 1\n\
	adds r1, r7\n\
	ldrh r2, [r1]\n\
	adds r0, r6, 0\n\
	ands r0, r2\n\
	mov r2, r12\n\
	orrs r0, r2\n\
	strh r0, [r1]\n\
	lsls r3, 24\n\
	asrs r1, r3, 23\n\
	adds r1, r7\n\
	adds r1, 0x40\n\
	ldrh r2, [r1]\n\
	adds r0, r6, 0\n\
	ands r0, r2\n\
	mov r5, r12\n\
	orrs r0, r5\n\
	strh r0, [r1]\n\
	b _0807241A\n\
_080723EA:\n\
	lsls r2, 1\n\
	adds r2, r7\n\
	ldrh r0, [r2]\n\
	adds r1, r6, 0\n\
	ands r1, r0\n\
	ldrb r0, [r5]\n\
	adds r0, 0x14\n\
	orrs r1, r0\n\
	strh r1, [r2]\n\
	lsls r4, r3, 24\n\
	asrs r3, r4, 24\n\
	lsls r2, r3, 1\n\
	adds r2, r7\n\
	adds r2, 0x40\n\
	ldrh r0, [r2]\n\
	adds r1, r6, 0\n\
	ands r1, r0\n\
	mov r5, sp\n\
	adds r0, r5, r3\n\
	ldrb r0, [r0]\n\
	adds r0, 0x34\n\
	orrs r1, r0\n\
	strh r1, [r2]\n\
	adds r3, r4, 0\n\
_0807241A:\n\
	movs r0, 0x80\n\
	lsls r0, 17\n\
	add r0, r8\n\
	lsrs r1, r0, 24\n\
	movs r2, 0x80\n\
	lsls r2, 17\n\
	adds r0, r3, r2\n\
	lsrs r3, r0, 24\n\
	asrs r0, 24\n\
	cmp r0, 0x3\n\
	ble _080723B4\n\
	b _08072496\n\
_08072432:\n\
	movs r3, 0\n\
	movs r4, 0xFC\n\
	lsls r4, 8\n\
	movs r6, 0x1E\n\
_0807243A:\n\
	lsls r1, r3, 24\n\
	asrs r2, r1, 24\n\
	mov r3, sp\n\
	adds r5, r3, r2\n\
	ldrb r0, [r5]\n\
	adds r3, r1, 0\n\
	cmp r0, 0xFF\n\
	bne _08072466\n\
	lsls r1, r2, 1\n\
	adds r1, r7\n\
	ldrh r2, [r1]\n\
	adds r0, r4, 0\n\
	ands r0, r2\n\
	orrs r0, r6\n\
	strh r0, [r1]\n\
	adds r1, 0x40\n\
	ldrh r2, [r1]\n\
	adds r0, r4, 0\n\
	ands r0, r2\n\
	orrs r0, r6\n\
	strh r0, [r1]\n\
	b _08072488\n\
_08072466:\n\
	lsls r2, 1\n\
	adds r2, r7\n\
	ldrh r0, [r2]\n\
	adds r1, r4, 0\n\
	ands r1, r0\n\
	ldrb r0, [r5]\n\
	adds r0, 0x14\n\
	orrs r1, r0\n\
	strh r1, [r2]\n\
	adds r2, 0x40\n\
	ldrh r0, [r2]\n\
	adds r1, r4, 0\n\
	ands r1, r0\n\
	ldrb r0, [r5]\n\
	adds r0, 0x34\n\
	orrs r1, r0\n\
	strh r1, [r2]\n\
_08072488:\n\
	movs r5, 0x80\n\
	lsls r5, 17\n\
	adds r0, r3, r5\n\
	lsrs r3, r0, 24\n\
	asrs r0, 24\n\
	cmp r0, 0x3\n\
	ble _0807243A\n\
_08072496:\n\
	add sp, 0x4\n\
	pop {r3-r5}\n\
	mov r8, r3\n\
	mov r9, r4\n\
	mov r10, r5\n\
	pop {r4-r7}\n\
	pop {r0}\n\
	bx r0\n\
        .syntax divided");
}

#endif // NONMATCHING

void sub_80724A8(s16 arg0, s16 arg1, u16 *arg2)
{
    arg2[4] = 0x1E;
    sub_8072308(arg1, arg2, 0);
    sub_8072308(arg0, arg2 + 5, 1);
}

u8 CreateBankHealthboxSprites(u8 bank)
{
    s16 data6 = 0;
    u8 healthboxSpriteId_1, healthboxSpriteId_2;
    u8 unkSpriteId;
    struct Sprite *unkSpritePtr;

    if (!IsDoubleBattle())
    {
        if (GetBankSide(bank) == SIDE_PLAYER)
        {
            healthboxSpriteId_1 = CreateSprite(&gUnknown_0832C140[0], 240, 160, 1);
            healthboxSpriteId_2 = CreateSpriteAtEnd(&gUnknown_0832C140[0], 240, 160, 1);

            gSprites[healthboxSpriteId_1].oam.shape = 0;

            gSprites[healthboxSpriteId_2].oam.shape = 0;
            gSprites[healthboxSpriteId_2].oam.tileNum += 64;
        }
        else
        {
            healthboxSpriteId_1 = CreateSprite(&gUnknown_0832C170[0], 240, 160, 1);
            healthboxSpriteId_2 = CreateSpriteAtEnd(&gUnknown_0832C170[0], 240, 160, 1);

            gSprites[healthboxSpriteId_2].oam.tileNum += 32;

            data6 = 2;
        }
        gSprites[healthboxSpriteId_1].oam.affineParam = healthboxSpriteId_2;
        gSprites[healthboxSpriteId_2].data5 = healthboxSpriteId_1;
        gSprites[healthboxSpriteId_2].callback = sub_8072924;
    }
    else
    {
        if (GetBankSide(bank) == SIDE_PLAYER)
        {
            healthboxSpriteId_1 = CreateSprite(&gUnknown_0832C140[GetBankIdentity(bank) / 2], 240, 160, 1);
            healthboxSpriteId_2 = CreateSpriteAtEnd(&gUnknown_0832C140[GetBankIdentity(bank) / 2], 240, 160, 1);

            gSprites[healthboxSpriteId_1].oam.affineParam = healthboxSpriteId_2;

            gSprites[healthboxSpriteId_2].data5 = healthboxSpriteId_1;
            gSprites[healthboxSpriteId_2].oam.tileNum += 32;
            gSprites[healthboxSpriteId_2].callback = sub_8072924;

            data6 = 1;
        }
        else
        {
            healthboxSpriteId_1 = CreateSprite(&gUnknown_0832C170[GetBankIdentity(bank) / 2], 240, 160, 1);
            healthboxSpriteId_2 = CreateSpriteAtEnd(&gUnknown_0832C170[GetBankIdentity(bank) / 2], 240, 160, 1);

            gSprites[healthboxSpriteId_1].oam.affineParam = healthboxSpriteId_2;

            gSprites[healthboxSpriteId_2].data5 = healthboxSpriteId_1;
            gSprites[healthboxSpriteId_2].oam.tileNum += 32;
            gSprites[healthboxSpriteId_2].callback = sub_8072924;

            data6 = 2;
        }
    }

    unkSpriteId = CreateSpriteAtEnd(&gUnknown_0832C1C0[gBanksByIdentity[bank]], 140, 60, 0);
    unkSpritePtr = &gSprites[unkSpriteId];
    SetSubspriteTables(unkSpritePtr, &gUnknown_0832C28C[GetBankSide(bank)]);
    unkSpritePtr->subspriteMode = 2;
    unkSpritePtr->oam.priority = 1;

    CpuCopy32(GetHealthboxElementGfxPtr(1), (void*)(OBJ_VRAM0 + unkSpritePtr->oam.tileNum * 32), 64);

    gSprites[healthboxSpriteId_1].data5 = unkSpriteId;
    gSprites[healthboxSpriteId_1].data6 = bank;
    gSprites[healthboxSpriteId_1].invisible = 1;

    gSprites[healthboxSpriteId_2].invisible = 1;

    unkSpritePtr->data5 = healthboxSpriteId_1;
    unkSpritePtr->data6 = data6;
    unkSpritePtr->invisible = 1;

    return healthboxSpriteId_1;
}

u8 CreateSafariPlayerHealthboxSprites(void)
{
    u8 healthboxSpriteId_1, healthboxSpriteId_2;

    healthboxSpriteId_1 = CreateSprite(&gUnknown_0832C1A0, 240, 160, 1);
    healthboxSpriteId_2 = CreateSpriteAtEnd(&gUnknown_0832C1A0, 240, 160, 1);

    gSprites[healthboxSpriteId_1].oam.shape = 0;
    gSprites[healthboxSpriteId_2].oam.shape = 0;

    gSprites[healthboxSpriteId_2].oam.tileNum += 64;

    gSprites[healthboxSpriteId_1].oam.affineParam = healthboxSpriteId_2;
    gSprites[healthboxSpriteId_2].data5 = healthboxSpriteId_1;

    gSprites[healthboxSpriteId_2].callback = sub_8072924;

    return healthboxSpriteId_1;
}

extern const u32 gHealthboxElementsGfxTable[][8];

const u32 *GetHealthboxElementGfxPtr(u8 elementId)
{
    return gHealthboxElementsGfxTable[elementId];
}

void sub_80728B4(struct Sprite *sprite)
{
    u8 var = sprite->data5;

    switch (sprite->data6)
    {
    case 0:
        sprite->pos1.x = gSprites[var].pos1.x + 16;
        sprite->pos1.y = gSprites[var].pos1.y;
        break;
    case 1:
        sprite->pos1.x = gSprites[var].pos1.x + 16;
        sprite->pos1.y = gSprites[var].pos1.y;
        break;
    case 2:
    default:
        sprite->pos1.x = gSprites[var].pos1.x + 8;
        sprite->pos1.y = gSprites[var].pos1.y;
        break;
    }

    sprite->pos2.x = gSprites[var].pos2.x;
    sprite->pos2.y = gSprites[var].pos2.y;
}

void sub_8072924(struct Sprite *sprite)
{
    u8 otherSpriteId = sprite->data5;

    sprite->pos1.x = gSprites[otherSpriteId].pos1.x + 64;
    sprite->pos1.y = gSprites[otherSpriteId].pos1.y;

    sprite->pos2.x = gSprites[otherSpriteId].pos2.x;
    sprite->pos2.y = gSprites[otherSpriteId].pos2.y;
}

void SetBattleBarStruct(u8 bank, u8 healthboxSpriteId, u32 maxVal, u32 currVal, bool32 isDoubleBattle)
{
    gBattleSpritesDataPtr->battleBars[bank].healthboxSpriteId = healthboxSpriteId;
    gBattleSpritesDataPtr->battleBars[bank].maxValue = maxVal;
    gBattleSpritesDataPtr->battleBars[bank].currentValue = currVal;
    gBattleSpritesDataPtr->battleBars[bank].isDoubleBattle = isDoubleBattle;
    gBattleSpritesDataPtr->battleBars[bank].field_10 = -32768;
}

void SetHealthboxSpriteInvisible(u8 healthboxSpriteId)
{
    gSprites[healthboxSpriteId].invisible = 1;
    gSprites[gSprites[healthboxSpriteId].data5].invisible = 1;
    gSprites[gSprites[healthboxSpriteId].oam.affineParam].invisible = 1;
}

void SetHealthboxSpriteVisible(u8 healthboxSpriteId)
{
    gSprites[healthboxSpriteId].invisible = 0;
    gSprites[gSprites[healthboxSpriteId].data5].invisible = 0;
    gSprites[gSprites[healthboxSpriteId].oam.affineParam].invisible = 0;
}

static void UpdateSpritePos(u8 spriteId, s16 x, s16 y)
{
    gSprites[spriteId].pos1.x = x;
    gSprites[spriteId].pos1.y = y;
}

void DestoryHealthboxSprite(u8 healthboxSpriteId)
{
    DestroySprite(&gSprites[gSprites[healthboxSpriteId].oam.affineParam]);
    DestroySprite(&gSprites[gSprites[healthboxSpriteId].data5]);
    DestroySprite(&gSprites[healthboxSpriteId]);
}

void nullsub_30(u8 healthboxSpriteId, bool8 isDoubleBattleBankOnly)
{

}

extern u8 gNoOfAllBanks;
extern u8 gHealthBoxesIds[BATTLE_BANKS_COUNT];

void UpdateOamPriorityInAllHealthboxes(u8 priority)
{
    s32 i;

    for (i = 0; i < gNoOfAllBanks; i++)
    {
        u8 healthboxSpriteId_1 = gHealthBoxesIds[i];
        u8 healthboxSpriteId_2 = gSprites[gHealthBoxesIds[i]].oam.affineParam;
        u8 healthboxSpriteId_3 = gSprites[gHealthBoxesIds[i]].data5;

        gSprites[healthboxSpriteId_1].oam.priority = priority;
        gSprites[healthboxSpriteId_2].oam.priority = priority;
        gSprites[healthboxSpriteId_3].oam.priority = priority;
    }
}

void SetBankHealthboxSpritePos(u8 bank)
{
    s16 x = 0, y = 0;

    if (!IsDoubleBattle())
    {
        if (GetBankSide(bank) != SIDE_PLAYER)
            x = 44, y = 30;
        else
            x = 158, y = 88;
    }
    else
    {
        switch (GetBankIdentity(bank))
        {
        case IDENTITY_PLAYER_MON1:
            x = 159, y = 76;
            break;
        case IDENTITY_PLAYER_MON2:
            x = 171, y = 101;
            break;
        case IDENTITY_OPPONENT_MON1:
            x = 44, y = 19;
            break;
        case IDENTITY_OPPONENT_MON2:
            x = 32, y = 44;
            break;
        }
    }

    UpdateSpritePos(gHealthBoxesIds[bank], x, y);
}

void UpdateLvlInHealthbox(u8 healthboxSpriteId, u8 lvl)
{
    u32 windowId, windowTileData, spriteTileNum;
    u8 text[16];
    u32 xPos, var1;
    void *objVram;

    text[0] = 0xF9;
    text[1] = 5;

    xPos = (u32) ConvertIntToDecimalStringN(text + 2, lvl, STR_CONV_MODE_LEFT_ALIGN, 3);
    // Alright, that part was unmatchable. It's basically doing:
    // xPos = 5 * (3 - (u32)(&text[2]));
    xPos--;
    xPos--;
    xPos -= ((u32)(text));
    var1 = (3 - xPos);
    xPos = 4 * var1;
    xPos += var1;

    windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, xPos, 3, 2, &windowId);
    spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * 32;

    if (GetBankSide(gSprites[healthboxSpriteId].data6) == SIDE_PLAYER)
    {
        objVram = (void*)(OBJ_VRAM0);
        if (!IsDoubleBattle())
            objVram += spriteTileNum + 0x820;
        else
            objVram += spriteTileNum + 0x420;
    }
    else
    {
        objVram = (void*)(OBJ_VRAM0);
        objVram += spriteTileNum + 0x400;
    }
    sub_8075198(objVram, windowTileData, 3);
    RemoveWindow_(windowId);
}

void UpdateHpTextInHealthbox(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent)
{
    u32 windowId, windowTileData, spriteTileNum;
    u8 text[32];
    void *objVram;

    if (GetBankSide(gSprites[healthboxSpriteId].data6) == SIDE_PLAYER && !IsDoubleBattle())
    {
        spriteTileNum = gSprites[healthboxSpriteId].oam.tileNum * 32;
        if (maxOrCurrent) // singles, max
        {
            ConvertIntToDecimalStringN(text, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
            windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, 0, 5, 2, &windowId);
            objVram = (void*)(OBJ_VRAM0);
            objVram += spriteTileNum + 0xB40;
            sub_8075170(objVram, windowTileData, 2);
            RemoveWindow_(windowId);
        }
        else // singles, current
        {
            ConvertIntToDecimalStringN(text, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
            text[3] = CHAR_SLASH;
            text[4] = EOS;
            windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, 4, 5, 2, &windowId);
            objVram = (void*)(OBJ_VRAM0);
            objVram += spriteTileNum + 0x3E0;
            sub_8075170(objVram, windowTileData, 1);
            objVram = (void*)(OBJ_VRAM0);
            objVram += spriteTileNum + 0xB00;
            sub_8075170(objVram, windowTileData + 0x20, 2);
            RemoveWindow_(windowId);
        }

    }
    else
    {
        u8 bank;

        memcpy(text, gUnknown_0832C3C4, sizeof(gUnknown_0832C3C4));
        bank = gSprites[healthboxSpriteId].data6;
        if (IsDoubleBattle() == TRUE || GetBankSide(bank) == SIDE_OPPONENT)
        {
            UpdateHpTextInHealthboxInDoubles(healthboxSpriteId, value, maxOrCurrent);
        }
        else
        {
            u32 var;
            u8 i;

            if (GetBankSide(gSprites[healthboxSpriteId].data6) == SIDE_PLAYER)
            {
                if (!maxOrCurrent)
                    var = 29;
                else
                    var = 89;
            }
            else
            {
                if (!maxOrCurrent)
                    var = 20;
                else
                    var = 48;
            }

            ConvertIntToDecimalStringN(text + 6, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
            RenderTextFont9(gMonSpritesGfxPtr->fontPixels, 9, text);

            for (i = 0; i < 3; i++)
            {
                CpuCopy32(&gMonSpritesGfxPtr->fontPixels[i * 64 + 32],
                          (void*)((OBJ_VRAM0) + 32 * (gSprites[healthboxSpriteId].oam.tileNum + var + i)),
                          0x20);
            }
        }
    }
}

extern const u8 gText_Slash[];

void UpdateHpTextInHealthboxInDoubles(u8 healthboxSpriteId, s16 value, u8 maxOrCurrent)
{
    u32 windowId, windowTileData, spriteTileNum;
    u8 text[32];
    void *objVram;

    if (GetBankSide(gSprites[healthboxSpriteId].data6) == SIDE_PLAYER)
    {
        if (gBattleSpritesDataPtr->bankData[gSprites[healthboxSpriteId].data6].hpNumbersNoBars) // don't print text if only bars are visible
        {
            spriteTileNum = gSprites[gSprites[healthboxSpriteId].data5].oam.tileNum * 32;
            objVram = (void*)(OBJ_VRAM0) + spriteTileNum;

            if (maxOrCurrent) // doubles, max hp
            {
                ConvertIntToDecimalStringN(text, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
                windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, 0, 5, 0, &windowId);
                sub_8075170((void*)(OBJ_VRAM0) + spriteTileNum + 0xC0, windowTileData, 2);
                RemoveWindow_(windowId);
                CpuCopy32(GetHealthboxElementGfxPtr(0x74),
                          (void*)(OBJ_VRAM0 + 0x680) + (gSprites[healthboxSpriteId].oam.tileNum * 32),
                           0x20);
            }
            else
            {
                ConvertIntToDecimalStringN(text, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
                text[3] = CHAR_SLASH;
                text[4] = EOS;
                windowTileData = AddTextPrinterAndCreateWindowOnHealthbox(text, 4, 5, 0, &windowId);
                sub_807513C(objVram, 0, 3);
                sub_8075170((void*)(OBJ_VRAM0 + 0x60) + spriteTileNum, windowTileData, 3);
                RemoveWindow_(windowId);
            }
        }
    }
    else
    {
        u8 bank;

        memcpy(text, gUnknown_0832C3D8, sizeof(gUnknown_0832C3D8));
        bank = gSprites[healthboxSpriteId].data6;

        if (gBattleSpritesDataPtr->bankData[bank].hpNumbersNoBars) // don't print text if only bars are visible
        {
            u8 var = 4;
            u8 r7;
            u8 *txtPtr;
            u8 i;

            if (!maxOrCurrent)
                var = 0;

            r7 = gSprites[healthboxSpriteId].data5;
            txtPtr = ConvertIntToDecimalStringN(text + 6, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
            if (!maxOrCurrent)
                StringCopy(txtPtr, gText_Slash);
            RenderTextFont9(gMonSpritesGfxPtr->fontPixels, 9, text);

            for (i = var; i < var + 3; i++)
            {
                if (i < 3)
                {
                    CpuCopy32(&gMonSpritesGfxPtr->fontPixels[((i - var) * 64) + 32],
                          (void*)((OBJ_VRAM0) + 32 * (1 + gSprites[r7].oam.tileNum + i)),
                          0x20);
                }
                else
                {
                    CpuCopy32(&gMonSpritesGfxPtr->fontPixels[((i - var) * 64) + 32],
                          (void*)((OBJ_VRAM0 + 0x20) + 32 * (i + gSprites[r7].oam.tileNum)),
                          0x20);
                }
            }

            if (!maxOrCurrent)
            {
                CpuCopy32(&gMonSpritesGfxPtr->fontPixels[224],
                          (void*)((OBJ_VRAM0) + ((gSprites[r7].oam.tileNum + 4) * 32)),
                          0x20);
                CpuFill32(0, (void*)((OBJ_VRAM0) + (gSprites[r7].oam.tileNum * 32)), 0x20);
            }
            else
            {
                if (GetBankSide(bank) == SIDE_PLAYER) // impossible to reach part, because the bank is from the opponent's side
                {
                    CpuCopy32(GetHealthboxElementGfxPtr(0x74),
                          (void*)(OBJ_VRAM0) + ((gSprites[healthboxSpriteId].oam.tileNum + 52) * 32),
                           0x20);
                }
            }
        }
    }
}
