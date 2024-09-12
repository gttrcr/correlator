def func31(domain, a1, a2, a3, a4):
    return a1 + a2 * domain[0] + a3 * domain[1] + a4 * domain[2]


def func32(domain, a1, a2, a3, a4, a5, a6, a7):
    return (
        a1
        + a2 * domain[0] ** 2
        + a3 * domain[0] * domain[1]
        + a4 * domain[0] * domain[2]
        + a5 * domain[1] ** 2
        + a6 * domain[1] * domain[2]
        + a7 * domain[2] ** 2
    )


def func33(domain, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10):
    return (
        a1
        + a2 * domain[0] ** 3
        + a3 * domain[0] ** 2 * domain[1]
        + a4 * domain[0] ** 2 * domain[2]
        + a5 * domain[0] * domain[1] ** 2
        + a6 * domain[0] * domain[1] * domain[2]
        + a7 * domain[0] * domain[2] ** 2
        + a8 * domain[1] ** 3
        + a9 * domain[1] ** 2 * domain[2]
        + a10 * domain[2] ** 3
    )


def func34(domain, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15):
    return (
        a1
        + a2 * domain[0] ** 4
        + a3 * domain[0] ** 3 * domain[1]
        + a4 * domain[0] ** 3 * domain[2]
        + a5 * domain[0] ** 2 * domain[1] ** 2
        + a6 * domain[0] ** 2 * domain[1] * domain[2]
        + a7 * domain[0] ** 2 * domain[2] ** 2
        + a8 * domain[0] * domain[1] ** 3
        + a9 * domain[0] * domain[1] ** 2 * domain[2]
        + a10 * domain[0] * domain[1] * domain[2] ** 2
        + a11 * domain[0] * domain[2] ** 3
        + a12 * domain[1] ** 4
        + a13 * domain[1] ** 3 * domain[2]
        + a14 * domain[1] ** 2 * domain[2] ** 2
        + a15 * domain[2] ** 4
    )


def func35(
    domain,
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
):
    return (
        a1
        + a2 * domain[0] ** 5
        + a3 * domain[0] ** 4 * domain[1]
        + a4 * domain[0] ** 4 * domain[2]
        + a5 * domain[0] ** 3 * domain[1] ** 2
        + a6 * domain[0] ** 3 * domain[1] * domain[2]
        + a7 * domain[0] ** 3 * domain[2] ** 2
        + a8 * domain[0] ** 2 * domain[1] ** 3
        + a9 * domain[0] ** 2 * domain[1] ** 2 * domain[2]
        + a10 * domain[0] ** 2 * domain[1] * domain[2] ** 2
        + a11 * domain[0] ** 2 * domain[2] ** 3
        + a12 * domain[0] * domain[1] ** 4
        + a13 * domain[0] * domain[1] ** 3 * domain[2]
        + a14 * domain[0] * domain[1] ** 2 * domain[2] ** 2
        + a15 * domain[0] * domain[1] * domain[2] ** 3
        + a16 * domain[0] * domain[2] ** 4
        + a17 * domain[1] ** 5
        + a18 * domain[1] ** 4 * domain[2]
        + a19 * domain[1] ** 3 * domain[2] ** 2
        + a20 * domain[1] ** 2 * domain[2] ** 3
        + a21 * domain[2] ** 5
    )


def func36(
    domain,
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
    a22,
    a23,
    a24,
    a25,
    a26,
    a27,
):
    return (
        a1
        + a2 * domain[0] ** 6
        + a3 * domain[0] ** 5 * domain[1]
        + a4 * domain[0] ** 5 * domain[2]
        + a5 * domain[0] ** 4 * domain[1] ** 2
        + a6 * domain[0] ** 4 * domain[1] * domain[2]
        + a7 * domain[0] ** 4 * domain[2] ** 2
        + a8 * domain[0] ** 3 * domain[1] ** 3
        + a9 * domain[0] ** 3 * domain[1] ** 2 * domain[2]
        + a10 * domain[0] ** 3 * domain[1] * domain[2] ** 2
        + a11 * domain[0] ** 3 * domain[2] ** 3
        + a12 * domain[0] ** 2 * domain[1] ** 4
        + a13 * domain[0] ** 2 * domain[1] ** 3 * domain[2]
        + a14 * domain[0] ** 2 * domain[1] ** 2 * domain[2] ** 2
        + a15 * domain[0] ** 2 * domain[1] * domain[2] ** 3
        + a16 * domain[0] ** 2 * domain[2] ** 4
        + a17 * domain[0] * domain[1] ** 5
        + a18 * domain[0] * domain[1] ** 4 * domain[2]
        + a19 * domain[0] * domain[1] ** 3 * domain[2] ** 2
        + a20 * domain[0] * domain[1] ** 2 * domain[2] ** 3
        + a21 * domain[0] * domain[1] * domain[2] ** 4
        + a22 * domain[0] * domain[2] ** 5
        + a23 * domain[1] ** 6
        + a24 * domain[1] ** 5 * domain[2]
        + a25 * domain[1] ** 4 * domain[2] ** 2
        + a26 * domain[1] ** 3 * domain[2] ** 3
        + a27 * domain[2] ** 6
    )


def func37(
    domain,
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
    a22,
    a23,
    a24,
    a25,
    a26,
    a27,
    a28,
    a29,
    a30,
    a31,
    a32,
):
    return (
        a1
        + a2 * domain[0] ** 7
        + a3 * domain[0] ** 6 * domain[1]
        + a4 * domain[0] ** 6 * domain[2]
        + a5 * domain[0] ** 5 * domain[1] ** 2
        + a6 * domain[0] ** 5 * domain[1] * domain[2]
        + a7 * domain[0] ** 5 * domain[2] ** 2
        + a8 * domain[0] ** 4 * domain[1] ** 3
        + a9 * domain[0] ** 4 * domain[1] ** 2 * domain[2]
        + a10 * domain[0] ** 4 * domain[1] * domain[2] ** 2
        + a11 * domain[0] ** 4 * domain[2] ** 3
        + a12 * domain[0] ** 3 * domain[1] ** 4
        + a13 * domain[0] ** 3 * domain[1] ** 3 * domain[2]
        + a14 * domain[0] ** 3 * domain[1] ** 2 * domain[2] ** 2
        + a15 * domain[0] ** 3 * domain[1] * domain[2] ** 3
        + a16 * domain[0] ** 3 * domain[2] ** 4
        + a17 * domain[0] ** 2 * domain[1] ** 5
        + a18 * domain[0] ** 2 * domain[1] ** 4 * domain[2]
        + a19 * domain[0] ** 2 * domain[1] ** 3 * domain[2] ** 2
        + a20 * domain[0] ** 2 * domain[1] ** 2 * domain[2] ** 3
        + a21 * domain[0] ** 2 * domain[1] * domain[2] ** 4
        + a22 * domain[0] ** 2 * domain[2] ** 5
        + a23 * domain[0] * domain[1] ** 6
        + a24 * domain[0] * domain[1] ** 5 * domain[2]
        + a25 * domain[0] * domain[1] ** 4 * domain[2] ** 2
        + a26 * domain[0] * domain[1] ** 3 * domain[2] ** 3
        + a27 * domain[0] * domain[1] ** 2 * domain[2] ** 4
        + a28 * domain[0] * domain[1] * domain[2] ** 5
        + a29 * domain[0] * domain[2] ** 6
        + a30 * domain[1] ** 7
        + a31 * domain[1] ** 6 * domain[2]
        + a32 * domain[1] ** 5 * domain[2] ** 2
    )


def func38(
    domain,
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
    a22,
    a23,
    a24,
    a25,
    a26,
    a27,
    a28,
    a29,
    a30,
    a31,
    a32,
    a33,
    a34,
    a35,
    a36,
):
    return (
        a1
        + a2 * domain[0] ** 8
        + a3 * domain[0] ** 7 * domain[1]
        + a4 * domain[0] ** 7 * domain[2]
        + a5 * domain[0] ** 6 * domain[1] ** 2
        + a6 * domain[0] ** 6 * domain[1] * domain[2]
        + a7 * domain[0] ** 6 * domain[2] ** 2
        + a8 * domain[0] ** 5 * domain[1] ** 3
        + a9 * domain[0] ** 5 * domain[1] ** 2 * domain[2]
        + a10 * domain[0] ** 5 * domain[1] * domain[2] ** 2
        + a11 * domain[0] ** 5 * domain[2] ** 3
        + a12 * domain[0] ** 4 * domain[1] ** 4
        + a13 * domain[0] ** 4 * domain[1] ** 3 * domain[2]
        + a14 * domain[0] ** 4 * domain[1] ** 2 * domain[2] ** 2
        + a15 * domain[0] ** 4 * domain[1] * domain[2] ** 3
        + a16 * domain[0] ** 4 * domain[2] ** 4
        + a17 * domain[0] ** 3 * domain[1] ** 5
        + a18 * domain[0] ** 3 * domain[1] ** 4 * domain[2]
        + a19 * domain[0] ** 3 * domain[1] ** 3 * domain[2] ** 2
        + a20 * domain[0] ** 3 * domain[1] ** 2 * domain[2] ** 3
        + a21 * domain[0] ** 3 * domain[1] * domain[2] ** 4
        + a22 * domain[0] ** 3 * domain[2] ** 5
        + a23 * domain[0] ** 2 * domain[1] ** 6
        + a24 * domain[0] ** 2 * domain[1] ** 5 * domain[2]
        + a25 * domain[0] ** 2 * domain[1] ** 4 * domain[2] ** 2
        + a26 * domain[0] ** 2 * domain[1] ** 3 * domain[2] ** 3
        + a27 * domain[0] ** 2 * domain[1] ** 2 * domain[2] ** 4
        + a28 * domain[0] ** 2 * domain[1] * domain[2] ** 5
        + a29 * domain[0] ** 2 * domain[2] ** 6
        + a30 * domain[0] * domain[1] ** 7
        + a31 * domain[0] * domain[1] ** 6 * domain[2]
        + a32 * domain[0] * domain[1] ** 5 * domain[2] ** 2
        + a33 * domain[0] * domain[1] ** 4 * domain[2] ** 3
        + a34 * domain[0] * domain[1] ** 3 * domain[2] ** 4
        + a35 * domain[0] * domain[1] ** 2 * domain[2] ** 5
        + a36 * domain[0] * domain[2] ** 7
    )


def func39(
    domain,
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
    a22,
    a23,
    a24,
    a25,
    a26,
    a27,
    a28,
    a29,
    a30,
    a31,
    a32,
    a33,
    a34,
    a35,
    a36,
    a37,
    a38,
    a39,
    a40,
):
    return (
        a1
        + a2 * domain[0] ** 9
        + a3 * domain[0] ** 8 * domain[1]
        + a4 * domain[0] ** 8 * domain[2]
        + a5 * domain[0] ** 7 * domain[1] ** 2
        + a6 * domain[0] ** 7 * domain[1] * domain[2]
        + a7 * domain[0] ** 7 * domain[2] ** 2
        + a8 * domain[0] ** 6 * domain[1] ** 3
        + a9 * domain[0] ** 6 * domain[1] ** 2 * domain[2]
        + a10 * domain[0] ** 6 * domain[1] * domain[2] ** 2
        + a11 * domain[0] ** 6 * domain[2] ** 3
        + a12 * domain[0] ** 5 * domain[1] ** 4
        + a13 * domain[0] ** 5 * domain[1] ** 3 * domain[2]
        + a14 * domain[0] ** 5 * domain[1] ** 2 * domain[2] ** 2
        + a15 * domain[0] ** 5 * domain[1] * domain[2] ** 3
        + a16 * domain[0] ** 5 * domain[2] ** 4
        + a17 * domain[0] ** 4 * domain[1] ** 5
        + a18 * domain[0] ** 4 * domain[1] ** 4 * domain[2]
        + a19 * domain[0] ** 4 * domain[1] ** 3 * domain[2] ** 2
        + a20 * domain[0] ** 4 * domain[1] ** 2 * domain[2] ** 3
        + a21 * domain[0] ** 4 * domain[1] * domain[2] ** 4
        + a22 * domain[0] ** 4 * domain[2] ** 5
        + a23 * domain[0] ** 3 * domain[1] ** 6
        + a24 * domain[0] ** 3 * domain[1] ** 5 * domain[2]
        + a25 * domain[0] ** 3 * domain[1] ** 4 * domain[2] ** 2
        + a26 * domain[0] ** 3 * domain[1] ** 3 * domain[2] ** 3
        + a27 * domain[0] ** 3 * domain[1] ** 2 * domain[2] ** 4
        + a28 * domain[0] ** 3 * domain[1] * domain[2] ** 5
        + a29 * domain[0] ** 3 * domain[2] ** 6
        + a30 * domain[0] ** 2 * domain[1] ** 7
        + a31 * domain[0] ** 2 * domain[1] ** 6 * domain[2]
        + a32 * domain[0] ** 2 * domain[1] ** 5 * domain[2] ** 2
        + a33 * domain[0] ** 2 * domain[1] ** 4 * domain[2] ** 3
        + a34 * domain[0] ** 2 * domain[1] ** 3 * domain[2] ** 4
        + a35 * domain[0] ** 2 * domain[1] ** 2 * domain[2] ** 5
        + a36 * domain[0] ** 2 * domain[1] * domain[2] ** 6
        + a37 * domain[0] ** 2 * domain[2] ** 7
        + a38 * domain[0] * domain[1] ** 8
        + a39 * domain[0] * domain[1] ** 7 * domain[2]
        + a40 * domain[0] * domain[1] ** 6 * domain[2] ** 2
    )


def func310(
    domain,
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    a11,
    a12,
    a13,
    a14,
    a15,
    a16,
    a17,
    a18,
    a19,
    a20,
    a21,
    a22,
    a23,
    a24,
    a25,
    a26,
    a27,
    a28,
    a29,
    a30,
    a31,
    a32,
    a33,
    a34,
    a35,
    a36,
    a37,
    a38,
    a39,
    a40,
    a41,
    a42,
    a43,
    a44,
    a45,
):
    return (
        a1
        + a2 * domain[0] ** 10
        + a3 * domain[0] ** 9 * domain[1]
        + a4 * domain[0] ** 9 * domain[2]
        + a5 * domain[0] ** 8 * domain[1] ** 2
        + a6 * domain[0] ** 8 * domain[1] * domain[2]
        + a7 * domain[0] ** 8 * domain[2] ** 2
        + a8 * domain[0] ** 7 * domain[1] ** 3
        + a9 * domain[0] ** 7 * domain[1] ** 2 * domain[2]
        + a10 * domain[0] ** 7 * domain[1] * domain[2] ** 2
        + a11 * domain[0] ** 7 * domain[2] ** 3
        + a12 * domain[0] ** 6 * domain[1] ** 4
        + a13 * domain[0] ** 6 * domain[1] ** 3 * domain[2]
        + a14 * domain[0] ** 6 * domain[1] ** 2 * domain[2] ** 2
        + a15 * domain[0] ** 6 * domain[1] * domain[2] ** 3
        + a16 * domain[0] ** 6 * domain[2] ** 4
        + a17 * domain[0] ** 5 * domain[1] ** 5
        + a18 * domain[0] ** 5 * domain[1] ** 4 * domain[2]
        + a19 * domain[0] ** 5 * domain[1] ** 3 * domain[2] ** 2
        + a20 * domain[0] ** 5 * domain[1] ** 2 * domain[2] ** 3
        + a21 * domain[0] ** 5 * domain[1] * domain[2] ** 4
        + a22 * domain[0] ** 5 * domain[2] ** 5
        + a23 * domain[0] ** 4 * domain[1] ** 6
        + a24 * domain[0] ** 4 * domain[1] ** 5 * domain[2]
        + a25 * domain[0] ** 4 * domain[1] ** 4 * domain[2] ** 2
        + a26 * domain[0] ** 4 * domain[1] ** 3 * domain[2] ** 3
        + a27 * domain[0] ** 4 * domain[1] ** 2 * domain[2] ** 4
        + a28 * domain[0] ** 4 * domain[1] * domain[2] ** 5
        + a29 * domain[0] ** 4 * domain[2] ** 6
        + a30 * domain[0] ** 3 * domain[1] ** 7
        + a31 * domain[0] ** 3 * domain[1] ** 6 * domain[2]
        + a32 * domain[0] ** 3 * domain[1] ** 5 * domain[2] ** 2
        + a33 * domain[0] ** 3 * domain[1] ** 4 * domain[2] ** 3
        + a34 * domain[0] ** 3 * domain[1] ** 3 * domain[2] ** 4
        + a35 * domain[0] ** 3 * domain[1] ** 2 * domain[2] ** 5
        + a36 * domain[0] ** 3 * domain[1] * domain[2] ** 6
        + a37 * domain[0] ** 3 * domain[2] ** 7
        + a38 * domain[0] ** 2 * domain[1] ** 8
        + a39 * domain[0] ** 2 * domain[1] ** 7 * domain[2]
        + a40 * domain[0] ** 2 * domain[1] ** 6 * domain[2] ** 2
        + a41 * domain[0] ** 2 * domain[1] ** 5 * domain[2] ** 3
        + a42 * domain[0] ** 2 * domain[1] ** 4 * domain[2] ** 4
        + a43 * domain[0] ** 2 * domain[1] ** 3 * domain[2] ** 5
        + a44 * domain[0] ** 2 * domain[1] ** 2 * domain[2] ** 6
        + a45 * domain[0] ** 2 * domain[2] ** 8
    )
