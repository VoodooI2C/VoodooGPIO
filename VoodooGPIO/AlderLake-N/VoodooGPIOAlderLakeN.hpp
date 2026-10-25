//
//  VoodooGPIOAlderLakeN.hpp
//  VoodooGPIO
//
//  Created by lzhoang2801 on 24/10/26.
//  Copyright © 2026 lzhoang2801. All rights reserved.
//

#ifndef VoodooGPIOAlderLakeN_hpp
#define VoodooGPIOAlderLakeN_hpp

#include "../VoodooGPIOIntel.hpp"

#define ADL_N_PAD_OWN    0x020
#define ADL_N_PADCFGLOCK    0x080
#define ADL_N_HOSTSW_OWN    0x0b0
#define ADL_N_GPI_IS    0x100
#define ADL_N_GPI_IE    0x120

#define ADL_N_NO_GPIO -1

#define ADL_N_GPP(r, s, e, g)         \
    {                                 \
        .reg_num = (r),               \
        .base = (s),                  \
        .size = ((e) - (s) + 1),      \
        .gpio_base = (g),             \
    }

#define ADL_N_COMMUNITY(b, s, e, g)               \
    {                                             \
        .barno = (b),                             \
        .padown_offset = ADL_N_PAD_OWN,           \
        .padcfglock_offset = ADL_N_PADCFGLOCK,    \
        .hostown_offset = ADL_N_HOSTSW_OWN,       \
        .is_offset = ADL_N_GPI_IS,                \
        .ie_offset = ADL_N_GPI_IE,                \
        .pin_base = (s),                          \
        .npins = ((e) - (s) + 1),                 \
        .gpps = (g),                              \
        .ngpps = ARRAY_SIZE(g),                   \
    }

static const struct pinctrl_pin_desc adln_pins[] = {
    /* GPP_B */
    PINCTRL_PIN(0, (char *)"CORE_VID_0"),
    PINCTRL_PIN(1, (char *)"CORE_VID_1"),
    PINCTRL_PIN(2, (char *)"GPPC_B_2"),
    PINCTRL_PIN(3, (char *)"GPPC_B_3"),
    PINCTRL_PIN(4, (char *)"GPPC_B_4"),
    PINCTRL_PIN(5, (char *)"GPPC_B_5"),
    PINCTRL_PIN(6, (char *)"GPPC_B_6"),
    PINCTRL_PIN(7, (char *)"GPPC_B_7"),
    PINCTRL_PIN(8, (char *)"GPPC_B_8"),
    PINCTRL_PIN(9, (char *)"GPPC_B_9"),
    PINCTRL_PIN(10, (char *)"GPPC_B_10"),
    PINCTRL_PIN(11, (char *)"GPPC_B_11"),
    PINCTRL_PIN(12, (char *)"SLP_S0B"),
    PINCTRL_PIN(13, (char *)"PLTRSTB"),
    PINCTRL_PIN(14, (char *)"GPPC_B_14"),
    PINCTRL_PIN(15, (char *)"GPPC_B_15"),
    PINCTRL_PIN(16, (char *)"GPPC_B_16"),
    PINCTRL_PIN(17, (char *)"GPPC_B_17"),
    PINCTRL_PIN(18, (char *)"GPPC_B_18"),
    PINCTRL_PIN(19, (char *)"GPPC_B_19"),
    PINCTRL_PIN(20, (char *)"GPPC_B_20"),
    PINCTRL_PIN(21, (char *)"GPPC_B_21"),
    PINCTRL_PIN(22, (char *)"GPPC_B_22"),
    PINCTRL_PIN(23, (char *)"GPPC_B_23"),
    PINCTRL_PIN(24, (char *)"GSPI0_CLK_LOOPBK"),
    PINCTRL_PIN(25, (char *)"GSPI1_CLK_LOOPBK"),
    /* GPP_T */
    PINCTRL_PIN(26, (char *)"GPPC_T_0"),
    PINCTRL_PIN(27, (char *)"GPPC_T_1"),
    PINCTRL_PIN(28, (char *)"FUSA_DIAGTEST_EN"),
    PINCTRL_PIN(29, (char *)"FUSA_DIAGTEST_MODE"),
    PINCTRL_PIN(30, (char *)"GPPC_T_4"),
    PINCTRL_PIN(31, (char *)"GPPC_T_5"),
    PINCTRL_PIN(32, (char *)"GPPC_T_6"),
    PINCTRL_PIN(33, (char *)"GPPC_T_7"),
    PINCTRL_PIN(34, (char *)"GPPC_T_8"),
    PINCTRL_PIN(35, (char *)"GPPC_T_9"),
    PINCTRL_PIN(36, (char *)"GPPC_T_10"),
    PINCTRL_PIN(37, (char *)"GPPC_T_11"),
    PINCTRL_PIN(38, (char *)"GPPC_T_12"),
    PINCTRL_PIN(39, (char *)"GPPC_T_13"),
    PINCTRL_PIN(40, (char *)"GPPC_T_14"),
    PINCTRL_PIN(41, (char *)"GPPC_T_15"),
    /* GPP_A */
    PINCTRL_PIN(42, (char *)"ESPI_IO_0"),
    PINCTRL_PIN(43, (char *)"ESPI_IO_1"),
    PINCTRL_PIN(44, (char *)"ESPI_IO_2"),
    PINCTRL_PIN(45, (char *)"ESPI_IO_3"),
    PINCTRL_PIN(46, (char *)"ESPI_CS0B"),
    PINCTRL_PIN(47, (char *)"ESPI_ALERT0B"),
    PINCTRL_PIN(48, (char *)"ESPI_ALERT1B"),
    PINCTRL_PIN(49, (char *)"GPPC_A_7"),
    PINCTRL_PIN(50, (char *)"GPPC_A_8"),
    PINCTRL_PIN(51, (char *)"ESPI_CLK"),
    PINCTRL_PIN(52, (char *)"ESPI_RESETB"),
    PINCTRL_PIN(53, (char *)"GPPC_A_11"),
    PINCTRL_PIN(54, (char *)"GPPC_A_12"),
    PINCTRL_PIN(55, (char *)"GPPC_A_13"),
    PINCTRL_PIN(56, (char *)"GPPC_A_14"),
    PINCTRL_PIN(57, (char *)"GPPC_A_15"),
    PINCTRL_PIN(58, (char *)"GPPC_A_16"),
    PINCTRL_PIN(59, (char *)"GPPC_A_17"),
    PINCTRL_PIN(60, (char *)"GPPC_A_18"),
    PINCTRL_PIN(61, (char *)"GPPC_A_19"),
    PINCTRL_PIN(62, (char *)"GPPC_A_20"),
    PINCTRL_PIN(63, (char *)"GPPC_A_21"),
    PINCTRL_PIN(64, (char *)"GPPC_A_22"),
    PINCTRL_PIN(65, (char *)"ESPI_CS1B"),
    PINCTRL_PIN(66, (char *)"ESPI_CLK_LOOPBK"),
    /* GPP_S */
    PINCTRL_PIN(67, (char *)"GPP_S_0"),
    PINCTRL_PIN(68, (char *)"GPP_S_1"),
    PINCTRL_PIN(69, (char *)"GPP_S_2"),
    PINCTRL_PIN(70, (char *)"GPP_S_3"),
    PINCTRL_PIN(71, (char *)"GPP_S_4"),
    PINCTRL_PIN(72, (char *)"GPP_S_5"),
    PINCTRL_PIN(73, (char *)"GPP_S_6"),
    PINCTRL_PIN(74, (char *)"GPP_S_7"),
    /* GPP_I */
    PINCTRL_PIN(75, (char *)"GPP_F_0_CNV_BRI_DT_UART0_RTSB"),
    PINCTRL_PIN(76, (char *)"GPP_F_1_CNV_BRI_RSP_UART0_RXD"),
    PINCTRL_PIN(77, (char *)"GPP_F_2_CNV_RGI_DT_UART0_TXD"),
    PINCTRL_PIN(78, (char *)"GPP_F_3_CNV_RGI_RSP_UART0_CTSB"),
    PINCTRL_PIN(79, (char *)"GPP_F_4_CNV_RF_RESET_B"),
    PINCTRL_PIN(80, (char *)"GPP_F_5_MODEM_CLKREQ"),
    PINCTRL_PIN(81, (char *)"GPP_F_6_CNV_PA_BLANKING"),
    PINCTRL_PIN(82, (char *)"GPP_F_7_EMMC_CMD"),
    PINCTRL_PIN(83, (char *)"GPP_F_8_EMMC_DATA0"),
    PINCTRL_PIN(84, (char *)"GPP_F_9_EMMC_DATA1"),
    PINCTRL_PIN(85, (char *)"GPP_F_10_EMMC_DATA2"),
    PINCTRL_PIN(86, (char *)"GPP_F_11_EMMC_DATA3"),
    PINCTRL_PIN(87, (char *)"GPP_F_12_EMMC_DATA4"),
    PINCTRL_PIN(88, (char *)"GPP_F_13_EMMC_DATA5"),
    PINCTRL_PIN(89, (char *)"GPP_F_14_EMMC_DATA6"),
    PINCTRL_PIN(90, (char *)"GPP_F_15_EMMC_DATA7"),
    PINCTRL_PIN(91, (char *)"GPP_F_16_EMMC_RCLK"),
    PINCTRL_PIN(92, (char *)"GPP_F_17_EMMC_CLK"),
    PINCTRL_PIN(93, (char *)"GPP_F_18_EMMC_RESETB"),
    PINCTRL_PIN(94, (char *)"GPP_F_19_A4WP_PRESENT"),
    /* GPP_H */
    PINCTRL_PIN(95, (char *)"GPPC_H_0"),
    PINCTRL_PIN(96, (char *)"GPPC_H_1"),
    PINCTRL_PIN(97, (char *)"GPPC_H_2"),
    PINCTRL_PIN(98, (char *)"GPPC_H_3"),
    PINCTRL_PIN(99, (char *)"GPPC_H_4"),
    PINCTRL_PIN(100, (char *)"GPPC_H_5"),
    PINCTRL_PIN(101, (char *)"GPPC_H_6"),
    PINCTRL_PIN(102, (char *)"GPPC_H_7"),
    PINCTRL_PIN(103, (char *)"GPPC_H_8"),
    PINCTRL_PIN(104, (char *)"GPPC_H_9"),
    PINCTRL_PIN(105, (char *)"GPPC_H_10"),
    PINCTRL_PIN(106, (char *)"GPPC_H_11"),
    PINCTRL_PIN(107, (char *)"I2C7_SDA"),
    PINCTRL_PIN(108, (char *)"I2C7_SCL"),
    PINCTRL_PIN(109, (char *)"GPPC_H_14"),
    PINCTRL_PIN(110, (char *)"GPPC_H_15"),
    PINCTRL_PIN(111, (char *)"GPPC_H_16"),
    PINCTRL_PIN(112, (char *)"GPPC_H_17"),
    PINCTRL_PIN(113, (char *)"CPU_C10_GATEB"),
    PINCTRL_PIN(114, (char *)"GPPC_H_19"),
    PINCTRL_PIN(115, (char *)"GPPC_H_20"),
    PINCTRL_PIN(116, (char *)"GPPC_H_21"),
    PINCTRL_PIN(117, (char *)"GPPC_H_22"),
    PINCTRL_PIN(118, (char *)"GPPC_H_23"),
    /* GPP_D */
    PINCTRL_PIN(119, (char *)"GPPC_D_0"),
    PINCTRL_PIN(120, (char *)"GPPC_D_1"),
    PINCTRL_PIN(121, (char *)"GPPC_D_2"),
    PINCTRL_PIN(122, (char *)"GPPC_D_3"),
    PINCTRL_PIN(123, (char *)"GPPC_D_4"),
    PINCTRL_PIN(124, (char *)"GPPC_D_5"),
    PINCTRL_PIN(125, (char *)"GPPC_D_6"),
    PINCTRL_PIN(126, (char *)"GPPC_D_7"),
    PINCTRL_PIN(127, (char *)"GPPC_D_8"),
    PINCTRL_PIN(128, (char *)"BSSB_LS2_RX"),
    PINCTRL_PIN(129, (char *)"BSSB_LS2_TX"),
    PINCTRL_PIN(130, (char *)"BSSB_LS3_RX"),
    PINCTRL_PIN(131, (char *)"BSSB_LS3_TX"),
    PINCTRL_PIN(132, (char *)"GPPC_D_13"),
    PINCTRL_PIN(133, (char *)"GPPC_D_14"),
    PINCTRL_PIN(134, (char *)"GPPC_D_15"),
    PINCTRL_PIN(135, (char *)"GPPC_D_16"),
    PINCTRL_PIN(136, (char *)"GPPC_D_17"),
    PINCTRL_PIN(137, (char *)"GPPC_D_18"),
    PINCTRL_PIN(138, (char *)"GPPC_D_19"),
    PINCTRL_PIN(139, (char *)"GSPI2_CLK_LOOPBK"),
    /* vGPIO */
    PINCTRL_PIN(140, (char *)"CNV_BTEN"),
    PINCTRL_PIN(141, (char *)"CNV_BT_HOST_WAKEB"),
    PINCTRL_PIN(142, (char *)"CNV_BT_IF_SELECT"),
    PINCTRL_PIN(143, (char *)"vCNV_BT_UART_TXD"),
    PINCTRL_PIN(144, (char *)"vCNV_BT_UART_RXD"),
    PINCTRL_PIN(145, (char *)"vCNV_BT_UART_CTS_B"),
    PINCTRL_PIN(146, (char *)"vCNV_BT_UART_RTS_B"),
    PINCTRL_PIN(147, (char *)"vCNV_MFUART1_TXD"),
    PINCTRL_PIN(148, (char *)"vCNV_MFUART1_RXD"),
    PINCTRL_PIN(149, (char *)"vCNV_MFUART1_CTS_B"),
    PINCTRL_PIN(150, (char *)"vCNV_MFUART1_RTS_B"),
    PINCTRL_PIN(151, (char *)"vUART0_TXD"),
    PINCTRL_PIN(152, (char *)"vUART0_RXD"),
    PINCTRL_PIN(153, (char *)"vUART0_CTS_B"),
    PINCTRL_PIN(154, (char *)"vUART0_RTS_B"),
    PINCTRL_PIN(155, (char *)"vISH_UART0_TXD"),
    PINCTRL_PIN(156, (char *)"vISH_UART0_RXD"),
    PINCTRL_PIN(157, (char *)"vISH_UART0_CTS_B"),
    PINCTRL_PIN(158, (char *)"vISH_UART0_RTS_B"),
    PINCTRL_PIN(159, (char *)"vCNV_BT_I2S_BCLK"),
    PINCTRL_PIN(160, (char *)"vCNV_BT_I2S_WS_SYNC"),
    PINCTRL_PIN(161, (char *)"vCNV_BT_I2S_SDO"),
    PINCTRL_PIN(162, (char *)"vCNV_BT_I2S_SDI"),
    PINCTRL_PIN(163, (char *)"vI2S2_SCLK"),
    PINCTRL_PIN(164, (char *)"vI2S2_SFRM"),
    PINCTRL_PIN(165, (char *)"vI2S2_TXD"),
    PINCTRL_PIN(166, (char *)"vI2S2_RXD"),
    PINCTRL_PIN(167, (char *)"THC0_WOT_INT"),
    PINCTRL_PIN(168, (char *)"THC1_WOT_INT"),
    /* GPP_C */
    PINCTRL_PIN(169, (char *)"SMBCLK"),
    PINCTRL_PIN(170, (char *)"SMBDATA"),
    PINCTRL_PIN(171, (char *)"SMBALERTB"),
    PINCTRL_PIN(172, (char *)"SML0CLK"),
    PINCTRL_PIN(173, (char *)"SML0DATA"),
    PINCTRL_PIN(174, (char *)"GPPC_C_5"),
    PINCTRL_PIN(175, (char *)"GPPC_C_6"),
    PINCTRL_PIN(176, (char *)"GPPC_C_7"),
    PINCTRL_PIN(177, (char *)"GPPC_C_8"),
    PINCTRL_PIN(178, (char *)"GPPC_C_9"),
    PINCTRL_PIN(179, (char *)"GPPC_C_10"),
    PINCTRL_PIN(180, (char *)"GPPC_C_11"),
    PINCTRL_PIN(181, (char *)"GPPC_C_12"),
    PINCTRL_PIN(182, (char *)"GPPC_C_13"),
    PINCTRL_PIN(183, (char *)"GPPC_C_14"),
    PINCTRL_PIN(184, (char *)"GPPC_C_15"),
    PINCTRL_PIN(185, (char *)"GPPC_C_16"),
    PINCTRL_PIN(186, (char *)"GPPC_C_17"),
    PINCTRL_PIN(187, (char *)"GPPC_C_18"),
    PINCTRL_PIN(188, (char *)"GPPC_C_19"),
    PINCTRL_PIN(189, (char *)"GPPC_C_20"),
    PINCTRL_PIN(190, (char *)"GPPC_C_21"),
    PINCTRL_PIN(191, (char *)"GPPC_C_22"),
    PINCTRL_PIN(192, (char *)"GPPC_C_23"),
    /* GPP_F */
    PINCTRL_PIN(193, (char *)"CNV_BRI_DT"),
    PINCTRL_PIN(194, (char *)"CNV_BRI_RSP"),
    PINCTRL_PIN(195, (char *)"CNV_RGI_DT"),
    PINCTRL_PIN(196, (char *)"CNV_RGI_RSP"),
    PINCTRL_PIN(197, (char *)"CNV_RF_RESET_B"),
    PINCTRL_PIN(198, (char *)"MODEM_CLKREQ"),
    PINCTRL_PIN(199, (char *)"GPPC_F_6"),
    PINCTRL_PIN(200, (char *)"GPPC_F_7"),
    PINCTRL_PIN(201, (char *)"GPPC_F_8"),
    PINCTRL_PIN(202, (char *)"BOOTMPC"),
    PINCTRL_PIN(203, (char *)"GPPC_F_10"),
    PINCTRL_PIN(204, (char *)"GPPC_F_11"),
    PINCTRL_PIN(205, (char *)"GPPC_F_12"),
    PINCTRL_PIN(206, (char *)"GPPC_F_13"),
    PINCTRL_PIN(207, (char *)"GPPC_F_14"),
    PINCTRL_PIN(208, (char *)"GPPC_F_15"),
    PINCTRL_PIN(209, (char *)"GPPC_F_16"),
    PINCTRL_PIN(210, (char *)"GPPC_F_17"),
    PINCTRL_PIN(211, (char *)"GPPC_F_18"),
    PINCTRL_PIN(212, (char *)"GPPC_F_19"),
    PINCTRL_PIN(213, (char *)"EXT_PWR_GATEB"),
    PINCTRL_PIN(214, (char *)"EXT_PWR_GATE2B"),
    PINCTRL_PIN(215, (char *)"GPPC_F_22"),
    PINCTRL_PIN(216, (char *)"GPPC_F_23"),
    PINCTRL_PIN(217, (char *)"GPPF_CLK_LOOPBACK"),
    /* HVCMOS */
    PINCTRL_PIN(218, (char *)"L_BKLTEN"),
    PINCTRL_PIN(219, (char *)"L_BKLTCTL"),
    PINCTRL_PIN(220, (char *)"L_VDDEN"),
    PINCTRL_PIN(221, (char *)"SYS_PWROK"),
    PINCTRL_PIN(222, (char *)"SYS_RESETB"),
    PINCTRL_PIN(223, (char *)"MLK_RSTB"),
    /* GPP_E */
    PINCTRL_PIN(224, (char *)"GPPC_E_0"),
    PINCTRL_PIN(225, (char *)"GPPC_E_1"),
    PINCTRL_PIN(226, (char *)"GPPC_E_2"),
    PINCTRL_PIN(227, (char *)"GPPC_E_3"),
    PINCTRL_PIN(228, (char *)"GPPC_E_4"),
    PINCTRL_PIN(229, (char *)"GPPC_E_5"),
    PINCTRL_PIN(230, (char *)"GPPC_E_6"),
    PINCTRL_PIN(231, (char *)"GPPC_E_7"),
    PINCTRL_PIN(232, (char *)"GPPC_E_8"),
    PINCTRL_PIN(233, (char *)"GPPC_E_9"),
    PINCTRL_PIN(234, (char *)"GPPC_E_10"),
    PINCTRL_PIN(235, (char *)"GPPC_E_11"),
    PINCTRL_PIN(236, (char *)"GPPC_E_12"),
    PINCTRL_PIN(237, (char *)"GPPC_E_13"),
    PINCTRL_PIN(238, (char *)"GPPC_E_14"),
    PINCTRL_PIN(239, (char *)"FIVR_DIGPB_0"),
    PINCTRL_PIN(240, (char *)"FIVR_DIGPB_1"),
    PINCTRL_PIN(241, (char *)"GPPC_E_17"),
    PINCTRL_PIN(242, (char *)"BSSB_LS0_RX"),
    PINCTRL_PIN(243, (char *)"BSSB_LS0_TX"),
    PINCTRL_PIN(244, (char *)"BSSB_LS1_RX"),
    PINCTRL_PIN(245, (char *)"BSSB_LS1_TX"),
    PINCTRL_PIN(246, (char *)"DNX_FORCE_RELOAD"),
    PINCTRL_PIN(247, (char *)"GPPC_E_23"),
    PINCTRL_PIN(248, (char *)"GPPE_CLK_LOOPBACK"),
    /* GPP_R */
    PINCTRL_PIN(249, (char *)"HDA_BCLK"),
    PINCTRL_PIN(250, (char *)"HDA_SYNC"),
    PINCTRL_PIN(251, (char *)"HDA_SDO"),
    PINCTRL_PIN(252, (char *)"HDA_SDI_0"),
    PINCTRL_PIN(253, (char *)"HDA_RSTB"),
    PINCTRL_PIN(254, (char *)"GPP_R_5"),
    PINCTRL_PIN(255, (char *)"GPP_R_6"),
    PINCTRL_PIN(256, (char *)"GPP_R_7"),
};

static struct intel_padgroup adln_community0_gpps[] = {
    ADL_N_GPP(0, 0, 25, 0),                /* GPP_B */
    ADL_N_GPP(1, 26, 41, 32),                /* GPP_T */
    ADL_N_GPP(2, 42, 66, 64),                /* GPP_A */
};

static struct intel_padgroup adln_community1_gpps[] = {
    ADL_N_GPP(0, 67, 74, 96),                /* GPP_S */
    ADL_N_GPP(1, 75, 94, 128),            /* GPP_I */
    ADL_N_GPP(2, 95, 118, 160),            /* GPP_H */
    ADL_N_GPP(3, 119, 139, 192),            /* GPP_D */
    ADL_N_GPP(4, 140, 168, 224),            /* vGPIO */
};

static struct intel_padgroup adln_community4_gpps[] = {
    ADL_N_GPP(0, 169, 192, 256),            /* GPP_C */
    ADL_N_GPP(1, 193, 217, 288),            /* GPP_F */
    ADL_N_GPP(2, 218, 223, ADL_N_NO_GPIO),    /* HVCMOS */
    ADL_N_GPP(3, 224, 248, 320),            /* GPP_E */
};

static struct intel_padgroup adln_community5_gpps[] = {
    ADL_N_GPP(0, 249, 256, 352),            /* GPP_R */
};

static struct intel_community adln_communities[] = {
    ADL_N_COMMUNITY(0, 0, 66, adln_community0_gpps),
    ADL_N_COMMUNITY(1, 67, 168, adln_community1_gpps),
    ADL_N_COMMUNITY(2, 169, 248, adln_community4_gpps),
    ADL_N_COMMUNITY(3, 249, 256, adln_community5_gpps),
};

class VoodooGPIOAlderLakeN : public VoodooGPIOIntel {
    OSDeclareDefaultStructors(VoodooGPIOAlderLakeN);

    bool start(IOService *provider) override;
};

#endif /* VoodooGPIOAlderLakeN_hpp */
