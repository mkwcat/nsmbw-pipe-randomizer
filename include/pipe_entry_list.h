#define ENT(_WLD, _LVL, _AREA, _ENT)                                           \
    (((_WLD - 1) << 24) | ((_LVL - 1) << 16) | ((_AREA - 1) << 8) | (_ENT))

#define GRP(...) 0x00001000 | __VA_ARGS__ | 0x00002000

static const u32 PipeEntryList[] = {
    // WORLD 1

    // 01-01
    //// Area 1
    ENT(1, 1, 1, 4), ENT(1, 1, 1, 5), ENT(1, 1, 1, 6), ENT(1, 1, 1, 7),
    ENT(1, 1, 1, 100), ENT(1, 1, 1, 101), ENT(1, 1, 1, 102), ENT(1, 1, 1, 103),
    //// Area 2
    GRP(ENT(1, 1, 2, 3), ENT(1, 1, 2, 4)),
    GRP(ENT(1, 1, 2, 5), ENT(1, 1, 2, 6)),

    // 01-02
    //// Area 1
    ENT(1, 2, 1, 1), GRP(ENT(1, 2, 1, 5)),
    //// Area 2
    GRP(ENT(1, 2, 2, 0), ENT(1, 2, 2, 1), ENT(1, 2, 2, 2), ENT(1, 2, 2, 3),
        ENT(1, 2, 2, 4), ENT(1, 2, 2, 8), ENT(1, 2, 2, 100), ENT(1, 2, 2, 101),
        ENT(1, 2, 2, 102), ENT(1, 2, 2, 103), ENT(1, 2, 2, 104),
        ENT(1, 2, 2, 105), ENT(1, 2, 2, 106), ENT(1, 2, 2, 107)),
    GRP(ENT(1, 2, 2, 5), ENT(1, 2, 2, 6)),
    GRP(ENT(1, 2, 2, 9), ENT(1, 2, 2, 10)),

    // 01-03
    //// Area 1
    ENT(1, 3, 1, 2), ENT(1, 3, 1, 3), ENT(1, 3, 1, 4), ENT(1, 3, 1, 6),
    ENT(1, 3, 1, 100), ENT(1, 3, 1, 101), ENT(1, 3, 1, 102), ENT(1, 3, 1, 103),
    ENT(1, 3, 1, 104), ENT(1, 3, 1, 105), ENT(1, 3, 1, 106), ENT(1, 3, 1, 107),
    ENT(1, 3, 1, 108),
    //// Area 2
    GRP(ENT(1, 3, 2, 0), ENT(1, 3, 2, 1)),
    GRP(ENT(1, 3, 2, 2), ENT(1, 3, 2, 3)),
    //// Area 3
    GRP(ENT(1, 3, 3, 0)),

    // 01-04
    //// Area 1
    ENT(1, 4, 1, 1), GRP(ENT(1, 4, 1, 2)),
    //// Area 2
    GRP(ENT(1, 4, 2, 1), ENT(1, 4, 2, 2), ENT(1, 4, 2, 3), ENT(1, 4, 2, 6),
        ENT(1, 4, 2, 100), ENT(1, 4, 2, 101), ENT(1, 4, 2, 102),
        ENT(1, 4, 2, 103), ENT(1, 4, 2, 104), ENT(1, 4, 2, 105),
        ENT(1, 4, 2, 106), ENT(1, 4, 2, 107), ENT(1, 4, 2, 108),
        ENT(1, 4, 2, 109), ENT(1, 4, 2, 110), ENT(1, 4, 2, 111),
        ENT(1, 4, 2, 112), ENT(1, 4, 2, 113)),
    GRP(ENT(1, 4, 2, 4), ENT(1, 4, 2, 5)),

    // Skip: 01-05

    // 01-06
    //// Area 1
    ENT(1, 6, 1, 1), ENT(1, 6, 1, 2), ENT(1, 6, 1, 7), ENT(1, 6, 1, 100),
    ENT(1, 6, 1, 101), ENT(1, 6, 1, 102),
    //// Area 2
    GRP(ENT(1, 6, 2, 0), ENT(1, 6, 2, 1), ENT(1, 6, 2, 100), ENT(1, 6, 2, 101)),
    //// Area 3
    ENT(1, 6, 3, 2), // Enterable via vine from area 1

    // 01-20 (Coin Battle)
    //// Area 1
    GRP(ENT(1, 20, 1, 1), ENT(1, 20, 1, 100), ENT(1, 20, 1, 101)),
    //// Area 2
    GRP(ENT(1, 20, 2, 1)),
    //// Skip: Area 3

    // Skip: 01-22 (Tower)

    // 01-24 (Castle)
    //// Area 1
    ENT(1, 24, 1, 3),
    GRP(ENT(1, 24, 1, 4)), // Exclusive because this pipe isn't accessible
    ENT(1, 24, 1, 7), ENT(1, 24, 1, 10), // Accessible via jumping
    //// Skip: Area 2
    //// Area 3
    GRP(ENT(1, 24, 3, 1), ENT(1, 24, 3, 2)),

    // WORLD 2

    // 02-01
    //// Area 1
    ENT(2, 1, 1, 100),

    // 02-02
    //// Area 1
    // ENT(2, 2, 1, 6),
    ENT(2, 2, 1, 7), ENT(2, 2, 1, 11),
    //// Area 2
    GRP(ENT(2, 2, 2, 1)), GRP(ENT(2, 2, 2, 8), ENT(2, 2, 2, 9)),
    //// Area 3
    ENT(2, 2, 3, 1), ENT(2, 2, 3, 3), // Last two accessible via quicksand pit
    GRP(ENT(2, 2, 3, 2)), GRP(ENT(2, 2, 3, 11)),

    // 02-03
    //// Area 1
    ENT(2, 3, 1, 1), GRP(ENT(2, 3, 1, 2), ENT(2, 3, 1, 4)),
    //// Area 2
    GRP(ENT(2, 3, 2, 0)),
    //// Area 3
    GRP(ENT(2, 3, 3, 0), ENT(2, 3, 3, 1)),
    //// Area 4
    GRP(ENT(2, 3, 4, 0), ENT(2, 3, 4, 1), ENT(2, 3, 4, 2), ENT(2, 3, 4, 3),
        ENT(2, 3, 4, 5), ENT(2, 3, 4, 6), ENT(2, 3, 4, 100), ENT(2, 3, 4, 101),
        ENT(2, 3, 4, 102), ENT(2, 3, 4, 103), ENT(2, 3, 4, 104),
        ENT(2, 3, 4, 105), ENT(2, 3, 4, 106)),

    // 02-04
    //// Area 1
    ENT(2, 4, 1, 2), ENT(2, 4, 1, 3), ENT(2, 4, 1, 4), ENT(2, 4, 1, 5),
    ENT(2, 4, 1, 7), ENT(2, 4, 1, 12), ENT(2, 4, 1, 13), ENT(2, 4, 1, 100),
    ENT(2, 4, 1, 101), ENT(2, 4, 1, 102), ENT(2, 4, 1, 103), ENT(2, 4, 1, 104),
    GRP(ENT(2, 4, 1, 8)), ENT(2, 4, 1, 10), // Accessible via vine
    GRP(ENT(2, 4, 1, 11)),
    //// Area 2
    GRP(ENT(2, 4, 2, 1), ENT(2, 4, 2, 2)),
    GRP(ENT(2, 4, 2, 3), ENT(2, 4, 2, 4)),

    // 02-05
    //// Area 1
    ENT(2, 5, 1, 2),
    //// Area 2
    ENT(2, 5, 2, 1), // Accessible via secret entrance

    // 02-06
    //// Area 1
    ENT(2, 6, 1, 2), ENT(2, 6, 1, 5), ENT(2, 6, 1, 6), ENT(2, 6, 1, 7),
    ENT(2, 6, 1, 100), ENT(2, 6, 1, 101), ENT(2, 6, 1, 102),
    GRP(ENT(2, 6, 1, 8)), GRP(ENT(2, 6, 1, 9)),
    //// Area 2
    GRP(ENT(2, 6, 2, 3), ENT(2, 6, 2, 4)),

    // 02-20 (Coin Battle)
    //// Area 1
    GRP(ENT(2, 20, 1, 100), ENT(2, 20, 1, 101), ENT(2, 20, 1, 102),
        ENT(2, 20, 1, 103), ENT(2, 20, 1, 104), ENT(2, 20, 1, 105)),
    //// Skip: Area 2

    // Skip: 02-22 (Tower)

    // 02-24 (Castle)
    //// Area 1
    ENT(2, 24, 1, 100), ENT(2, 24, 1, 101), ENT(2, 24, 1, 102),
    //// Skip: Area 2

    // WORLD 3

    // 03-01
    //// Area 1
    ENT(3, 1, 1, 1), ENT(3, 1, 1, 100), ENT(3, 1, 1, 101), ENT(3, 1, 1, 102),
    ENT(3, 1, 1, 103), ENT(3, 1, 1, 104),
    //// Area 2
    GRP(ENT(3, 1, 2, 0), ENT(3, 1, 2, 1), ENT(3, 1, 2, 100), ENT(3, 1, 2, 101)),
    //// Area 3
    GRP(ENT(3, 1, 3, 0)),

    // 03-02
    //// Area 1
    ENT(3, 2, 1, 2), ENT(3, 2, 1, 3),
    //// Area 2
    GRP(ENT(3, 2, 2, 1), ENT(3, 2, 2, 2)),

    // 03-03
    //// Area 1
    ENT(3, 3, 1, 1), ENT(3, 3, 1, 2),
    //// Area 2
    GRP(ENT(3, 3, 2, 0), ENT(3, 3, 2, 1), ENT(3, 3, 2, 100)),
    //// Area 3
    GRP(ENT(3, 3, 3, 0), ENT(3, 3, 3, 1), ENT(3, 3, 3, 3)),
    GRP(ENT(3, 3, 3, 4)), GRP(ENT(3, 3, 3, 2), ENT(3, 3, 3, 6)),

    // 03-04
    //// Area 1
    ENT(3, 4, 1, 2), ENT(3, 4, 1, 100),
    //// Area 2
    GRP(ENT(3, 4, 2, 0), ENT(3, 4, 2, 1)),
    //// Area 3
    GRP(ENT(3, 4, 3, 0)),

    // 03-05
    //// Area 1
    ENT(3, 5, 1, 1), GRP(ENT(3, 5, 1, 3), ENT(3, 5, 1, 4)), ENT(3, 5, 1, 6),
    //// Area 2
    GRP(ENT(3, 5, 2, 5)), GRP(ENT(3, 5, 2, 7)),

    // Skip: 03-20 (Coin Battle)

    // 03-21 (Ghost House)
    //// Area 1
    ENT(3, 21, 1, 0), ENT(3, 21, 1, 7), ENT(3, 21, 1, 100), ENT(3, 21, 1, 101),
    GRP(ENT(3, 21, 1, 4)), GRP(ENT(3, 21, 1, 5)),
    GRP(ENT(3, 21, 1, 6), ENT(3, 21, 1, 2)),
    //// Area 2
    GRP(ENT(3, 21, 2, 0), ENT(3, 21, 2, 3), ENT(3, 21, 2, 4),
        ENT(3, 21, 2, 100)),
    //// Area 3
    GRP(ENT(3, 21, 3, 0)), GRP(ENT(3, 21, 3, 1)),
    //// Area 4
    GRP(ENT(3, 21, 4, 1)), GRP(ENT(3, 21, 4, 5)),

    // Skip: 03-22 (Tower)

    // 03-24 (Castle)
    //// Area 1
    ENT(3, 24, 1, 2), GRP(ENT(3, 24, 1, 3)), ENT(3, 24, 1, 4), ENT(3, 24, 1, 7),
    GRP(ENT(3, 24, 1, 8), ENT(3, 24, 1, 10)), ENT(3, 24, 1, 9),
    GRP(ENT(3, 24, 1, 5), ENT(3, 24, 1, 100)),
    //// Skip: Area 2

    // WORLD 4

    // 04-01
    //// Area 1
    ENT(4, 1, 1, 1), GRP(ENT(4, 1, 1, 2)), // This pipe is inaccessible
    ENT(4, 1, 1, 4), ENT(4, 1, 1, 5), ENT(4, 1, 1, 100), ENT(4, 1, 1, 101),
    ENT(4, 1, 1, 102), ENT(4, 1, 1, 103), ENT(4, 1, 1, 104), ENT(4, 1, 1, 105),
    ENT(4, 1, 1, 106), ENT(4, 1, 1, 107), ENT(4, 1, 1, 108), ENT(4, 1, 1, 109),
    ENT(4, 1, 1, 110),
    //// Area 2
    GRP(ENT(4, 1, 2, 0), ENT(4, 1, 2, 1)),
    //// Area 3
    GRP(ENT(4, 1, 3, 0), ENT(4, 1, 3, 1)),

    // Skip: 04-02

    // 04-03
    //// Area 1
    // ENT(4, 3, 1, 2),
    GRP(ENT(4, 3, 1, 3), ENT(4, 3, 1, 4)), ENT(4, 3, 1, 5), ENT(4, 3, 1, 6),
    GRP(ENT(4, 3, 1, 7)),

    // 04-04
    //// Area 1
    ENT(4, 4, 1, 1), GRP(ENT(4, 4, 1, 2)),
    GRP(ENT(4, 4, 1, 3), ENT(4, 4, 1, 4)),
    //// Area 2
    GRP(ENT(4, 4, 2, 1), ENT(4, 4, 2, 2), ENT(4, 4, 2, 4), ENT(4, 4, 2, 5),
        ENT(4, 4, 2, 6), ENT(4, 4, 2, 9), ENT(4, 4, 2, 100), ENT(4, 4, 2, 101),
        ENT(4, 4, 2, 102), ENT(4, 4, 2, 103), ENT(4, 4, 2, 104),
        ENT(4, 4, 2, 105), ENT(4, 4, 2, 106), ENT(4, 4, 2, 107),
        ENT(4, 4, 2, 108), ENT(4, 4, 2, 109), ENT(4, 4, 2, 110),
        ENT(4, 4, 2, 113), ENT(4, 4, 2, 114), ENT(4, 4, 2, 115),
        ENT(4, 4, 2, 116), ENT(4, 4, 2, 117), ENT(4, 4, 2, 118),
        ENT(4, 4, 2, 119), ENT(4, 4, 2, 120), ENT(4, 4, 2, 121),
        ENT(4, 4, 2, 122)),

    GRP(ENT(4, 4, 2, 7), ENT(4, 4, 2, 8)),

    // 04-05
    //// Area 1
    ENT(4, 5, 1, 2), GRP(ENT(4, 5, 1, 3), ENT(4, 5, 1, 4)), ENT(4, 5, 1, 5),
    ENT(4, 5, 1, 100), ENT(4, 5, 1, 101), ENT(4, 5, 1, 102), ENT(4, 5, 1, 103),
    ENT(4, 5, 1, 104), ENT(4, 5, 1, 105), ENT(4, 5, 1, 106), ENT(4, 5, 1, 107),
    ENT(4, 5, 1, 108), ENT(4, 5, 1, 109), ENT(4, 5, 1, 110), ENT(4, 5, 1, 111),

    // Skip: 04-20 (Coin Battle)

    // 04-21 (Ghost House)
    //// Area 1
    ENT(4, 21, 1, 0), ENT(4, 21, 1, 1), ENT(4, 21, 1, 2),
    //// Area 2
    GRP(ENT(4, 21, 2, 0), ENT(4, 21, 2, 2), ENT(4, 21, 2, 3)),
    //// Area 3
    GRP(ENT(4, 21, 3, 0), ENT(4, 21, 3, 2), ENT(4, 21, 3, 100),
        ENT(4, 21, 3, 101), ENT(4, 21, 3, 102)),
    //// Area 4
    GRP(ENT(4, 21, 4, 1)), GRP(ENT(4, 21, 4, 2)), GRP(ENT(4, 21, 4, 16)),

    // 04-22 (Tower)
    //// Area 1
    ENT(4, 22, 1, 1), GRP(ENT(4, 22, 1, 2)),
    GRP(ENT(4, 22, 1, 3)), // 2 is not reachable from 3
    GRP(ENT(4, 22, 1, 4), ENT(4, 22, 1, 5)),
    GRP(ENT(4, 22, 1, 6), ENT(4, 22, 1, 8)),
    //// Skip: Area 2
    //// Area 3
    GRP(ENT(4, 22, 3, 1)),

    // 04-24 (Castle)
    //// Skip: Area 1
    //// Skip: Area 2
    //// Area 3
    ENT(4, 24, 3, 1), ENT(4, 24, 3, 7), // Last 2 reachable via door
    GRP(ENT(4, 24, 3, 3), ENT(4, 24, 3, 4)),
    GRP(ENT(4, 24, 3, 6), ENT(4, 24, 3, 8)),
    //// Area 4
    GRP(ENT(4, 24, 4, 0)), GRP(ENT(4, 24, 4, 2)),

    // 04-38 (Airship)
    //// Area 1
    ENT(4, 38, 1, 1), ENT(4, 38, 1, 3), GRP(ENT(4, 38, 1, 4), ENT(4, 38, 1, 5)),
    ENT(4, 38, 1, 6), GRP(ENT(4, 38, 1, 8)), ENT(4, 38, 1, 100),
    ENT(4, 38, 1, 101), ENT(4, 38, 1, 102),

    // WORLD 5

    // 05-01
    //// Area 1
    ENT(5, 1, 1, 3), ENT(5, 1, 1, 4), GRP(ENT(5, 1, 1, 5)), // Not enterable
    ENT(5, 1, 1, 6), // Reachable from 5
    //// Area 2
    GRP(ENT(5, 1, 2, 0), ENT(5, 1, 2, 1)),

    // 05-02
    //// Area 1
    ENT(5, 2, 1, 1), GRP(ENT(5, 2, 1, 2)),
    //// Area 2
    GRP(ENT(5, 2, 2, 1), ENT(5, 2, 2, 2), ENT(5, 2, 2, 9), ENT(5, 2, 2, 13),
        ENT(5, 2, 2, 17)),
    ENT(5, 2, 2, 8), ENT(5, 2, 2, 12),
    ENT(5, 2, 2, 16), // Last 3: Reachable via jumping entrance

    // 05-03
    //// Area 1
    ENT(5, 3, 1, 2), GRP(ENT(5, 3, 1, 3)), ENT(5, 3, 1, 4), ENT(5, 3, 1, 6),
    ENT(5, 3, 1, 100),
    //// Area 2
    GRP(ENT(5, 3, 2, 0)),
    //// Area 3
    GRP(ENT(5, 3, 3, 0)),

    // 05-04
    //// Area 1
    ENT(5, 4, 1, 1), GRP(ENT(5, 4, 1, 2)), ENT(5, 4, 1, 3),
    GRP(ENT(5, 4, 1, 4)),

    // 05-05
    //// Area 1
    ENT(5, 5, 1, 2), GRP(ENT(5, 5, 1, 3)),

    // 05-20 (Coin Battle)
    //// Area 1
    ENT(5, 20, 1, 1),
    //// Area 2
    GRP(ENT(5, 20, 2, 2)),

    // 05-21 (Ghost House)
    //// Area 1
    ENT(5, 21, 1, 0), ENT(5, 21, 1, 1), ENT(5, 21, 1, 2), ENT(5, 21, 1, 3),
    ENT(5, 21, 1, 4), ENT(5, 21, 1, 5), ENT(5, 21, 1, 100), ENT(5, 21, 1, 101),
    GRP(ENT(5, 21, 1, 16), ENT(5, 21, 1, 17)),
    GRP(ENT(5, 21, 1, 32), ENT(5, 21, 1, 33)),
    //// Area 2
    GRP(ENT(5, 21, 2, 0), ENT(5, 21, 2, 1)),
    //// Area 3
    GRP(ENT(5, 21, 3, 0), ENT(5, 21, 3, 3), ENT(5, 21, 3, 100),
        ENT(5, 21, 3, 101), ENT(5, 21, 3, 102)),
    GRP(ENT(5, 21, 3, 7), ENT(5, 21, 3, 8)),
    //// Area 4
    GRP(ENT(5, 21, 4, 0)), GRP(ENT(5, 21, 4, 16)),

    // Skip: 05-22 (Tower)

    // Skip: 05-24 (Castle)

    // WORLD 6

    // 06-01
    //// Area 1
    ENT(6, 1, 1, 2),
    GRP(ENT(6, 1, 1, 5)), // I'd say 5 is not reachable, at least not feasibly
    //// Area 2
    GRP(ENT(6, 1, 2, 3), ENT(6, 1, 2, 4)),

    // 06-02
    //// Area 1
    ENT(6, 2, 1, 1),
    //// Area 2
    GRP(ENT(6, 2, 2, 1)),
    //// Area 3
    GRP(ENT(6, 2, 3, 0), ENT(6, 2, 3, 1)),
    //// Area 4
    GRP(ENT(6, 2, 4, 0), ENT(6, 2, 4, 2), ENT(6, 2, 4, 3), ENT(6, 2, 4, 6),
        ENT(6, 2, 4, 100)),

    // 06-03
    //// Area 1
    ENT(6, 3, 1, 1), ENT(6, 3, 1, 100),

    GRP(ENT(6, 3, 1, 4), ENT(6, 3, 1, 102)), ENT(6, 3, 1, 3),
    ENT(6, 3, 1, 101), // Last 2: Reachable from 4 and 102

    GRP(ENT(6, 3, 1, 2), ENT(6, 3, 1, 103), ENT(6, 3, 1, 104),
        ENT(6, 3, 1, 105), ENT(6, 3, 1, 106), ENT(6, 3, 1, 107),
        ENT(6, 3, 1, 108)),

    //// Area 2
    // These are non-pipe entrances but they count anyway
    GRP(ENT(6, 3, 2, 1), ENT(6, 3, 2, 3), ENT(6, 3, 2, 4), ENT(6, 3, 2, 5)),

    // 06-04
    //// Area 1
    ENT(6, 4, 1, 2), ENT(6, 4, 1, 3), ENT(6, 4, 1, 4), GRP(ENT(6, 4, 1, 5)),
    //// Area 2
    GRP(ENT(6, 4, 2, 1), ENT(6, 4, 2, 2)),

    // 06-05
    //// Area 1
    ENT(6, 5, 1, 1),
    //// Area 2
    GRP(ENT(6, 5, 2, 0)),

    // 06-06
    //// Area 1
    GRP(ENT(6, 6, 1, 2)), GRP(ENT(6, 6, 1, 3)),
    //// Area 2
    GRP(ENT(6, 6, 2, 2), ENT(6, 6, 2, 4)),
    GRP(ENT(6, 6, 2, 5), ENT(6, 6, 2, 6)),

    // 06-22 (Tower)
    //// Area 1
    ENT(6, 22, 1, 2), ENT(6, 22, 1, 4),
    //// Skip: Area 2
    //// Area 3
    GRP(ENT(6, 22, 3, 1), ENT(6, 22, 3, 2)),

    // 06-24 (Castle)
    //// Area 1
    ENT(6, 24, 1, 1), GRP(ENT(6, 24, 1, 2)),
    //// Skip: Area 2

    // 06-38 (Airship)
    //// Area 1
    ENT(6, 38, 1, 1), GRP(ENT(6, 38, 1, 2)), ENT(6, 38, 1, 3),
    GRP(ENT(6, 38, 1, 4)), // Autoscroll is limiting here
    ENT(6, 38, 1, 5), ENT(6, 38, 1, 6),

    // WORLD 7

    // 07-01
    //// Area 1
    ENT(7, 1, 1, 1), ENT(7, 1, 1, 2),
    //// Area 2
    GRP(ENT(7, 1, 2, 1), ENT(7, 1, 2, 2), ENT(7, 1, 2, 3), ENT(7, 1, 2, 4),
        ENT(7, 1, 2, 100), ENT(7, 1, 2, 101), ENT(7, 1, 2, 102),
        ENT(7, 1, 2, 103), ENT(7, 1, 2, 104), ENT(7, 1, 2, 105),
        ENT(7, 1, 2, 106), ENT(7, 1, 2, 107), ENT(7, 1, 2, 108),
        ENT(7, 1, 2, 109), ENT(7, 1, 2, 110), ENT(7, 1, 2, 111),
        ENT(7, 1, 2, 112), ENT(7, 1, 2, 113), ENT(7, 1, 2, 114),
        ENT(7, 1, 2, 115), ENT(7, 1, 2, 116), ENT(7, 1, 2, 117),
        ENT(7, 1, 2, 118), ENT(7, 1, 2, 119), ENT(7, 1, 2, 120),
        ENT(7, 1, 2, 121)),

    GRP(ENT(7, 1, 2, 5), ENT(7, 1, 2, 6)),

    // 07-02
    //// Area 1
    ENT(7, 2, 1, 1), ENT(7, 2, 1, 2), GRP(ENT(7, 2, 1, 3), ENT(7, 2, 1, 4)),

    // Skip: 07-03

    // 07-04
    //// Area 1
    ENT(7, 4, 1, 100), ENT(7, 4, 1, 101), ENT(7, 4, 1, 1),

    GRP(ENT(7, 4, 1, 2), ENT(7, 4, 1, 3), ENT(7, 4, 1, 102), ENT(7, 4, 1, 103),
        ENT(7, 4, 1, 104), ENT(7, 4, 1, 105), ENT(7, 4, 1, 106),
        ENT(7, 4, 1, 107)),

    GRP(ENT(7, 4, 1, 4), ENT(7, 4, 1, 5), ENT(7, 4, 1, 108), ENT(7, 4, 1, 109),
        ENT(7, 4, 1, 110), ENT(7, 4, 1, 111)),

    GRP(ENT(7, 4, 1, 6), ENT(7, 4, 1, 7), ENT(7, 4, 1, 9), ENT(7, 4, 1, 112),
        ENT(7, 4, 1, 113), ENT(7, 4, 1, 114), ENT(7, 4, 1, 115)),

    GRP(ENT(7, 4, 1, 10), ENT(7, 4, 1, 11)),

    GRP(ENT(7, 4, 1, 8)),

    // 07-05
    //// Area 1
    ENT(7, 5, 1, 100),

    // 07-06
    //// Area 1
    ENT(7, 6, 1, 1), ENT(7, 6, 1, 2), GRP(ENT(7, 6, 1, 3), ENT(7, 6, 1, 4)),

    // 07-21 (Ghost House)
    //// Area 1
    ENT(7, 21, 1, 0), ENT(7, 21, 1, 1), ENT(7, 21, 1, 2), ENT(7, 21, 1, 100),
    //// Area 2
    GRP(ENT(7, 21, 2, 0), ENT(7, 21, 2, 1)),
    //// Area 3
    // 0 is unreachable from the other entrances in the area
    GRP(ENT(7, 21, 3, 0)),
    GRP(ENT(7, 21, 3, 6), ENT(7, 21, 3, 100), ENT(7, 21, 3, 101),
        ENT(7, 21, 3, 102), ENT(7, 21, 3, 103)),
    GRP(ENT(7, 21, 3, 1), ENT(7, 21, 3, 3)),
    GRP(ENT(7, 21, 3, 2), ENT(7, 21, 3, 104)),
    //// Area 4
    GRP(ENT(7, 21, 4, 0)), GRP(ENT(7, 21, 4, 16)), GRP(ENT(7, 21, 4, 18)),

    // 07-22 (Tower)
    //// Area 1
    ENT(7, 22, 1, 1), GRP(ENT(7, 22, 1, 5)),
    //// Skip: Area 2
    //// Area 3
    ENT(7, 22, 3, 2),
    ENT(7, 22, 3, 7), // Strange situation: 7 here will always have an entrance
    // from the beginning of the level

    // 07-24 (Castle)
    //// Area 1
    ENT(7, 24, 1, 3), ENT(7, 24, 1, 5), ENT(7, 24, 1, 6), ENT(7, 24, 1, 8),

    GRP(ENT(7, 24, 1, 7), ENT(7, 24, 1, 9)),
    //// Skip: Area 2

    // WORLD 8

    // 08-01
    //// Area 1
    ENT(8, 1, 1, 1), ENT(8, 1, 1, 3), GRP(ENT(8, 1, 1, 2), ENT(8, 1, 1, 4)),

    // 08-02
    //// Area 1
    ENT(8, 2, 1, 1),
    GRP(ENT(8, 2, 1, 2), ENT(8, 2, 1, 3), ENT(8, 2, 1, 6), ENT(8, 2, 1, 100)),
    GRP(ENT(8, 2, 1, 4)), GRP(ENT(8, 2, 1, 7)),

    //// Area 2
    GRP(ENT(8, 2, 2, 3), ENT(8, 2, 2, 4), ENT(8, 2, 2, 5), ENT(8, 2, 2, 100)),

    // 08-03
    //// Area 1
    ENT(8, 3, 1, 4), GRP(ENT(8, 3, 1, 5)),

    // 08-04
    //// Area 1
    ENT(8, 4, 1, 1),
    //// Area 2
    GRP(ENT(8, 4, 2, 0), ENT(8, 4, 2, 1), ENT(8, 4, 2, 7)),
    GRP(ENT(8, 4, 2, 2), ENT(8, 4, 2, 3)),
    GRP(ENT(8, 4, 2, 4), ENT(8, 4, 2, 6), ENT(8, 4, 2, 100), ENT(8, 4, 2, 101),
        ENT(8, 4, 2, 102), ENT(8, 4, 2, 103)),
    GRP(ENT(8, 4, 2, 9)),

    //// Area 3
    GRP(ENT(8, 4, 3, 0)),

    // 08-05
    //// Area 1
    ENT(8, 5, 1, 2), GRP(ENT(8, 5, 1, 3)),

    // 08-06
    //// Area 1
    ENT(8, 6, 1, 2), GRP(ENT(8, 6, 1, 3)), GRP(ENT(8, 6, 1, 4)),
    GRP(ENT(8, 6, 1, 5)),

    // 08-07
    //// Area 1
    ENT(8, 7, 1, 1),
    //// Area 2
    GRP(ENT(8, 7, 2, 1)),

    // Skip: 08-22 (Tower)

    // 08-24 (Castle)
    //// Area 1
    ENT(8, 24, 1, 1),
    //// Area 2
    GRP(ENT(8, 24, 2, 2)),
    //// Area 3
    GRP(ENT(8, 24, 3, 4)),
    //// Skip: Area 4

    // 08-38 (Airship)
    //// Area 1
    GRP(ENT(8, 38, 1, 2)), ENT(8, 38, 1, 3),
    // Next two are in the same area, but 4 is unreachable from 5
    GRP(ENT(8, 38, 1, 4)), GRP(ENT(8, 38, 1, 5)),
    // Same with these two
    GRP(ENT(8, 38, 1, 6)), GRP(ENT(8, 38, 1, 1)),

    // WORLD 9

    // 09-01
    //// Area 1
    ENT(9, 1, 1, 1), ENT(9, 1, 1, 4), ENT(9, 1, 1, 100), ENT(9, 1, 1, 101),
    ENT(9, 1, 1, 102), ENT(9, 1, 1, 103),
    //// Area 2
    GRP(ENT(9, 1, 2, 0), ENT(9, 1, 2, 1)),

    // 09-02
    //// Area 1
    ENT(9, 2, 1, 2), ENT(9, 2, 1, 5), ENT(9, 2, 1, 100), ENT(9, 2, 1, 101),
    ENT(9, 2, 1, 102), ENT(9, 2, 1, 103), ENT(9, 2, 1, 104),
    //// Area 2
    GRP(ENT(9, 2, 2, 3), ENT(9, 2, 2, 4), ENT(9, 2, 2, 100), ENT(9, 2, 2, 101),
        ENT(9, 2, 2, 102), ENT(9, 2, 2, 103), ENT(9, 2, 2, 104)),

    // 09-03
    //// Area 1
    ENT(9, 3, 1, 1), ENT(9, 3, 1, 2), ENT(9, 3, 1, 4), ENT(9, 3, 1, 5),
    GRP(ENT(9, 3, 1, 7), ENT(9, 3, 1, 8)), GRP(ENT(9, 3, 1, 11)),
    //// Area 2
    GRP(ENT(9, 3, 2, 2)),

    // 09-04
    //// Area 1
    ENT(9, 4, 1, 2), ENT(9, 4, 1, 4), ENT(9, 4, 1, 100), ENT(9, 4, 1, 101),
    ENT(9, 4, 1, 102), ENT(9, 4, 1, 103), ENT(9, 4, 1, 104), ENT(9, 4, 1, 105),
    ENT(9, 4, 1, 106), ENT(9, 4, 1, 107), ENT(9, 4, 1, 108), ENT(9, 4, 1, 109),
    ENT(9, 4, 1, 110), ENT(9, 4, 1, 111), ENT(9, 4, 1, 112), ENT(9, 4, 1, 113),
    ENT(9, 4, 1, 114), ENT(9, 4, 1, 115), ENT(9, 4, 1, 116), ENT(9, 4, 1, 117),

    GRP(ENT(9, 4, 1, 3)), // Not accessible from these other pipes
    GRP(ENT(9, 4, 1, 5), ENT(9, 4, 1, 118), ENT(9, 4, 1, 119),
        ENT(9, 4, 1, 120), ENT(9, 4, 1, 121), ENT(9, 4, 1, 122)),

    // 09-05
    //// Area 1
    ENT(9, 5, 1, 2), GRP(ENT(9, 5, 1, 3)),

    // 09-06
    //// Area 1
    ENT(9, 6, 1, 2), GRP(ENT(9, 6, 1, 3)),

    // 09-07
    //// Area 1
    ENT(9, 7, 1, 100), ENT(9, 7, 1, 101), ENT(9, 7, 1, 102), ENT(9, 7, 1, 103),
    ENT(9, 7, 1, 104), ENT(9, 7, 1, 105), ENT(9, 7, 1, 106), ENT(9, 7, 1, 107),
    ENT(9, 7, 1, 108), ENT(9, 7, 1, 109), ENT(9, 7, 1, 110), ENT(9, 7, 1, 111),
    ENT(9, 7, 1, 112), ENT(9, 7, 1, 113), ENT(9, 7, 1, 114), ENT(9, 7, 1, 115),
    ENT(9, 7, 1, 116), ENT(9, 7, 1, 117), ENT(9, 7, 1, 118), ENT(9, 7, 1, 119),
    ENT(9, 7, 1, 120), ENT(9, 7, 1, 121),

    // This entrance will be skipped if the entry count is an odd number
    GRP(ENT(2, 20, 2, 1)),

    // Skip: 09-08
};

const u32 PipeEntryCount = (sizeof(PipeEntryList) / 4) & ~1;
