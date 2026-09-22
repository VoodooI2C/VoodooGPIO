//
//  VoodooGPIOAlderLakeS.hpp
//  VoodooGPIO
//
//  Alder Lake-S PCH GPIO controller (ACPI INTC1085 / INTC1056). Raptor Lake-S
//  and the Raptor Lake-HX mobile parts use the same PCH and the same tables.
//  Pin, pad-group and community data follow Linux
//  drivers/pinctrl/intel/pinctrl-alderlake.c (adls_*).
//

#include "../VoodooGPIOIntel.hpp"

#ifndef VoodooGPIOAlderLakeS_hpp
#define VoodooGPIOAlderLakeS_hpp

#define ADL_S_PAD_OWN       0x0a0
#define ADL_S_PADCFGLOCK    0x110
#define ADL_S_HOSTSW_OWN    0x150
#define ADL_S_GPI_IS        0x200
#define ADL_S_GPI_IE        0x220

#define ADL_S_GPP(r, s, e, g)               \
    {                        \
        .reg_num = (r),                \
        .base = (s),                \
        .size = ((e) - (s) + 1),        \
        .gpio_base = (g),            \
    }

#define ADL_S_NO_GPIO     -1

#define ADL_S_COMMUNITY(b, s, e, g)            \
    {                                           \
        .barno = (b),                           \
        .padown_offset = ADL_S_PAD_OWN,           \
        .padcfglock_offset = ADL_S_PADCFGLOCK,    \
        .hostown_offset = ADL_S_HOSTSW_OWN,       \
        .is_offset = ADL_S_GPI_IS,                \
        .ie_offset = ADL_S_GPI_IE,                \
        .pin_base = (s),                        \
        .npins = ((e) - (s) + 1),               \
        .gpps = (g),                            \
        .ngpps = ARRAY_SIZE(g),                 \
    }

/* Alder Lake-S */
static struct pinctrl_pin_desc adls_pins[] = {
    /* GPP_I */
    PINCTRL_PIN(0, (char *)"EXT_PWR_GATEB"),
    PINCTRL_PIN(1, (char *)"DDSP_HPD_1"),
    PINCTRL_PIN(2, (char *)"DDSP_HPD_2"),
    PINCTRL_PIN(3, (char *)"DDSP_HPD_3"),
    PINCTRL_PIN(4, (char *)"DDSP_HPD_4"),
    PINCTRL_PIN(5, (char *)"DDPB_CTRLCLK"),
    PINCTRL_PIN(6, (char *)"DDPB_CTRLDATA"),
    PINCTRL_PIN(7, (char *)"DDPC_CTRLCLK"),
    PINCTRL_PIN(8, (char *)"DDPC_CTRLDATA"),
    PINCTRL_PIN(9, (char *)"GSPI0_CS1B"),
    PINCTRL_PIN(10, (char *)"GSPI1_CS1B"),
    PINCTRL_PIN(11, (char *)"USB2_OCB_4"),
    PINCTRL_PIN(12, (char *)"USB2_OCB_5"),
    PINCTRL_PIN(13, (char *)"USB2_OCB_6"),
    PINCTRL_PIN(14, (char *)"USB2_OCB_7"),
    PINCTRL_PIN(15, (char *)"GSPI0_CS0B"),
    PINCTRL_PIN(16, (char *)"GSPI0_CLK"),
    PINCTRL_PIN(17, (char *)"GSPI0_MISO"),
    PINCTRL_PIN(18, (char *)"GSPI0_MOSI"),
    PINCTRL_PIN(19, (char *)"GSPI1_CS0B"),
    PINCTRL_PIN(20, (char *)"GSPI1_CLK"),
    PINCTRL_PIN(21, (char *)"GSPI1_MISO"),
    PINCTRL_PIN(22, (char *)"GSPI1_MOSI"),
    PINCTRL_PIN(23, (char *)"GSPI0_CLK_LOOPBK"),
    PINCTRL_PIN(24, (char *)"GSPI1_CLK_LOOPBK"),
    /* GPP_R */
    PINCTRL_PIN(25, (char *)"HDA_BCLK"),
    PINCTRL_PIN(26, (char *)"HDA_SYNC"),
    PINCTRL_PIN(27, (char *)"HDA_SDO"),
    PINCTRL_PIN(28, (char *)"HDA_SDI_0"),
    PINCTRL_PIN(29, (char *)"HDA_RSTB"),
    PINCTRL_PIN(30, (char *)"HDA_SDI_1"),
    PINCTRL_PIN(31, (char *)"GPP_R_6"),
    PINCTRL_PIN(32, (char *)"GPP_R_7"),
    PINCTRL_PIN(33, (char *)"GPP_R_8"),
    PINCTRL_PIN(34, (char *)"DDSP_HPD_A"),
    PINCTRL_PIN(35, (char *)"DDSP_HPD_B"),
    PINCTRL_PIN(36, (char *)"DDSP_HPD_C"),
    PINCTRL_PIN(37, (char *)"ISH_SPI_CSB"),
    PINCTRL_PIN(38, (char *)"ISH_SPI_CLK"),
    PINCTRL_PIN(39, (char *)"ISH_SPI_MISO"),
    PINCTRL_PIN(40, (char *)"ISH_SPI_MOSI"),
    PINCTRL_PIN(41, (char *)"DDP1_CTRLCLK"),
    PINCTRL_PIN(42, (char *)"DDP1_CTRLDATA"),
    PINCTRL_PIN(43, (char *)"DDP2_CTRLCLK"),
    PINCTRL_PIN(44, (char *)"DDP2_CTRLDATA"),
    PINCTRL_PIN(45, (char *)"DDPA_CTRLCLK"),
    PINCTRL_PIN(46, (char *)"DDPA_CTRLDATA"),
    PINCTRL_PIN(47, (char *)"GSPI2_CLK_LOOPBK"),
    /* GPP_J */
    PINCTRL_PIN(48, (char *)"CNV_PA_BLANKING"),
    PINCTRL_PIN(49, (char *)"CPU_C10_GATEB"),
    PINCTRL_PIN(50, (char *)"CNV_BRI_DT"),
    PINCTRL_PIN(51, (char *)"CNV_BRI_RSP"),
    PINCTRL_PIN(52, (char *)"CNV_RGI_DT"),
    PINCTRL_PIN(53, (char *)"CNV_RGI_RSP"),
    PINCTRL_PIN(54, (char *)"CNV_MFUART2_RXD"),
    PINCTRL_PIN(55, (char *)"CNV_MFUART2_TXD"),
    PINCTRL_PIN(56, (char *)"SRCCLKREQB_16"),
    PINCTRL_PIN(57, (char *)"SRCCLKREQB_17"),
    PINCTRL_PIN(58, (char *)"BSSB_LS_RX"),
    PINCTRL_PIN(59, (char *)"BSSB_LS_TX"),
    /* vGPIO */
    PINCTRL_PIN(60, (char *)"CNV_BTEN"),
    PINCTRL_PIN(61, (char *)"CNV_BT_HOST_WAKEB"),
    PINCTRL_PIN(62, (char *)"CNV_BT_IF_SELECT"),
    PINCTRL_PIN(63, (char *)"vCNV_BT_UART_TXD"),
    PINCTRL_PIN(64, (char *)"vCNV_BT_UART_RXD"),
    PINCTRL_PIN(65, (char *)"vCNV_BT_UART_CTS_B"),
    PINCTRL_PIN(66, (char *)"vCNV_BT_UART_RTS_B"),
    PINCTRL_PIN(67, (char *)"vCNV_MFUART1_TXD"),
    PINCTRL_PIN(68, (char *)"vCNV_MFUART1_RXD"),
    PINCTRL_PIN(69, (char *)"vCNV_MFUART1_CTS_B"),
    PINCTRL_PIN(70, (char *)"vCNV_MFUART1_RTS_B"),
    PINCTRL_PIN(71, (char *)"vUART0_TXD"),
    PINCTRL_PIN(72, (char *)"vUART0_RXD"),
    PINCTRL_PIN(73, (char *)"vUART0_CTS_B"),
    PINCTRL_PIN(74, (char *)"vUART0_RTS_B"),
    PINCTRL_PIN(75, (char *)"vISH_UART0_TXD"),
    PINCTRL_PIN(76, (char *)"vISH_UART0_RXD"),
    PINCTRL_PIN(77, (char *)"vISH_UART0_CTS_B"),
    PINCTRL_PIN(78, (char *)"vISH_UART0_RTS_B"),
    PINCTRL_PIN(79, (char *)"vCNV_BT_I2S_BCLK"),
    PINCTRL_PIN(80, (char *)"vCNV_BT_I2S_WS_SYNC"),
    PINCTRL_PIN(81, (char *)"vCNV_BT_I2S_SDO"),
    PINCTRL_PIN(82, (char *)"vCNV_BT_I2S_SDI"),
    PINCTRL_PIN(83, (char *)"vI2S2_SCLK"),
    PINCTRL_PIN(84, (char *)"vI2S2_SFRM"),
    PINCTRL_PIN(85, (char *)"vI2S2_TXD"),
    PINCTRL_PIN(86, (char *)"vI2S2_RXD"),
    /* vGPIO_0 */
    PINCTRL_PIN(87, (char *)"ESPI_USB_OCB_0"),
    PINCTRL_PIN(88, (char *)"ESPI_USB_OCB_1"),
    PINCTRL_PIN(89, (char *)"ESPI_USB_OCB_2"),
    PINCTRL_PIN(90, (char *)"ESPI_USB_OCB_3"),
    PINCTRL_PIN(91, (char *)"USB_CPU_OCB_0"),
    PINCTRL_PIN(92, (char *)"USB_CPU_OCB_1"),
    PINCTRL_PIN(93, (char *)"USB_CPU_OCB_2"),
    PINCTRL_PIN(94, (char *)"USB_CPU_OCB_3"),
    /* GPP_B */
    PINCTRL_PIN(95, (char *)"PCIE_LNK_DOWN"),
    PINCTRL_PIN(96, (char *)"ISH_UART0_RTSB"),
    PINCTRL_PIN(97, (char *)"VRALERTB"),
    PINCTRL_PIN(98, (char *)"CPU_GP_2"),
    PINCTRL_PIN(99, (char *)"CPU_GP_3"),
    PINCTRL_PIN(100, (char *)"SX_EXIT_HOLDOFFB"),
    PINCTRL_PIN(101, (char *)"CLKOUT_48"),
    PINCTRL_PIN(102, (char *)"ISH_GP_7"),
    PINCTRL_PIN(103, (char *)"ISH_GP_0"),
    PINCTRL_PIN(104, (char *)"ISH_GP_1"),
    PINCTRL_PIN(105, (char *)"ISH_GP_2"),
    PINCTRL_PIN(106, (char *)"I2S_MCLK"),
    PINCTRL_PIN(107, (char *)"SLP_S0B"),
    PINCTRL_PIN(108, (char *)"PLTRSTB"),
    PINCTRL_PIN(109, (char *)"SPKR"),
    PINCTRL_PIN(110, (char *)"ISH_GP_3"),
    PINCTRL_PIN(111, (char *)"ISH_GP_4"),
    PINCTRL_PIN(112, (char *)"ISH_GP_5"),
    PINCTRL_PIN(113, (char *)"PMCALERTB"),
    PINCTRL_PIN(114, (char *)"FUSA_DIAGTEST_EN"),
    PINCTRL_PIN(115, (char *)"FUSA_DIAGTEST_MODE"),
    PINCTRL_PIN(116, (char *)"GPP_B_21"),
    PINCTRL_PIN(117, (char *)"GPP_B_22"),
    PINCTRL_PIN(118, (char *)"SML1ALERTB"),
    /* GPP_G */
    PINCTRL_PIN(119, (char *)"GPP_G_0"),
    PINCTRL_PIN(120, (char *)"GPP_G_1"),
    PINCTRL_PIN(121, (char *)"DNX_FORCE_RELOAD"),
    PINCTRL_PIN(122, (char *)"GMII_MDC_0"),
    PINCTRL_PIN(123, (char *)"GMII_MDIO_0"),
    PINCTRL_PIN(124, (char *)"SLP_DRAMB"),
    PINCTRL_PIN(125, (char *)"GPP_G_6"),
    PINCTRL_PIN(126, (char *)"GPP_G_7"),
    /* GPP_H */
    PINCTRL_PIN(127, (char *)"SRCCLKREQB_18"),
    PINCTRL_PIN(128, (char *)"GPP_H_1"),
    PINCTRL_PIN(129, (char *)"SRCCLKREQB_8"),
    PINCTRL_PIN(130, (char *)"SRCCLKREQB_9"),
    PINCTRL_PIN(131, (char *)"SRCCLKREQB_10"),
    PINCTRL_PIN(132, (char *)"SRCCLKREQB_11"),
    PINCTRL_PIN(133, (char *)"SRCCLKREQB_12"),
    PINCTRL_PIN(134, (char *)"SRCCLKREQB_13"),
    PINCTRL_PIN(135, (char *)"SRCCLKREQB_14"),
    PINCTRL_PIN(136, (char *)"SRCCLKREQB_15"),
    PINCTRL_PIN(137, (char *)"SML2CLK"),
    PINCTRL_PIN(138, (char *)"SML2DATA"),
    PINCTRL_PIN(139, (char *)"SML2ALERTB"),
    PINCTRL_PIN(140, (char *)"SML3CLK"),
    PINCTRL_PIN(141, (char *)"SML3DATA"),
    PINCTRL_PIN(142, (char *)"SML3ALERTB"),
    PINCTRL_PIN(143, (char *)"SML4CLK"),
    PINCTRL_PIN(144, (char *)"SML4DATA"),
    PINCTRL_PIN(145, (char *)"SML4ALERTB"),
    PINCTRL_PIN(146, (char *)"ISH_I2C0_SDA"),
    PINCTRL_PIN(147, (char *)"ISH_I2C0_SCL"),
    PINCTRL_PIN(148, (char *)"ISH_I2C1_SDA"),
    PINCTRL_PIN(149, (char *)"ISH_I2C1_SCL"),
    PINCTRL_PIN(150, (char *)"TIME_SYNC_0"),
    /* SPI0 */
    PINCTRL_PIN(151, (char *)"SPI0_IO_2"),
    PINCTRL_PIN(152, (char *)"SPI0_IO_3"),
    PINCTRL_PIN(153, (char *)"SPI0_MOSI_IO_0"),
    PINCTRL_PIN(154, (char *)"SPI0_MISO_IO_1"),
    PINCTRL_PIN(155, (char *)"SPI0_TPM_CSB"),
    PINCTRL_PIN(156, (char *)"SPI0_FLASH_0_CSB"),
    PINCTRL_PIN(157, (char *)"SPI0_FLASH_1_CSB"),
    PINCTRL_PIN(158, (char *)"SPI0_CLK"),
    PINCTRL_PIN(159, (char *)"SPI0_CLK_LOOPBK"),
    /* GPP_A */
    PINCTRL_PIN(160, (char *)"ESPI_IO_0"),
    PINCTRL_PIN(161, (char *)"ESPI_IO_1"),
    PINCTRL_PIN(162, (char *)"ESPI_IO_2"),
    PINCTRL_PIN(163, (char *)"ESPI_IO_3"),
    PINCTRL_PIN(164, (char *)"ESPI_CS0B"),
    PINCTRL_PIN(165, (char *)"ESPI_CLK"),
    PINCTRL_PIN(166, (char *)"ESPI_RESETB"),
    PINCTRL_PIN(167, (char *)"ESPI_CS1B"),
    PINCTRL_PIN(168, (char *)"ESPI_CS2B"),
    PINCTRL_PIN(169, (char *)"ESPI_CS3B"),
    PINCTRL_PIN(170, (char *)"ESPI_ALERT0B"),
    PINCTRL_PIN(171, (char *)"ESPI_ALERT1B"),
    PINCTRL_PIN(172, (char *)"ESPI_ALERT2B"),
    PINCTRL_PIN(173, (char *)"ESPI_ALERT3B"),
    PINCTRL_PIN(174, (char *)"GPP_A_14"),
    PINCTRL_PIN(175, (char *)"ESPI_CLK_LOOPBK"),
    /* GPP_C */
    PINCTRL_PIN(176, (char *)"SMBCLK"),
    PINCTRL_PIN(177, (char *)"SMBDATA"),
    PINCTRL_PIN(178, (char *)"SMBALERTB"),
    PINCTRL_PIN(179, (char *)"ISH_UART0_RXD"),
    PINCTRL_PIN(180, (char *)"ISH_UART0_TXD"),
    PINCTRL_PIN(181, (char *)"SML0ALERTB"),
    PINCTRL_PIN(182, (char *)"ISH_I2C2_SDA"),
    PINCTRL_PIN(183, (char *)"ISH_I2C2_SCL"),
    PINCTRL_PIN(184, (char *)"UART0_RXD"),
    PINCTRL_PIN(185, (char *)"UART0_TXD"),
    PINCTRL_PIN(186, (char *)"UART0_RTSB"),
    PINCTRL_PIN(187, (char *)"UART0_CTSB"),
    PINCTRL_PIN(188, (char *)"UART1_RXD"),
    PINCTRL_PIN(189, (char *)"UART1_TXD"),
    PINCTRL_PIN(190, (char *)"UART1_RTSB"),
    PINCTRL_PIN(191, (char *)"UART1_CTSB"),
    PINCTRL_PIN(192, (char *)"I2C0_SDA"),
    PINCTRL_PIN(193, (char *)"I2C0_SCL"),
    PINCTRL_PIN(194, (char *)"I2C1_SDA"),
    PINCTRL_PIN(195, (char *)"I2C1_SCL"),
    PINCTRL_PIN(196, (char *)"UART2_RXD"),
    PINCTRL_PIN(197, (char *)"UART2_TXD"),
    PINCTRL_PIN(198, (char *)"UART2_RTSB"),
    PINCTRL_PIN(199, (char *)"UART2_CTSB"),
    /* GPP_S */
    PINCTRL_PIN(200, (char *)"SNDW1_CLK"),
    PINCTRL_PIN(201, (char *)"SNDW1_DATA"),
    PINCTRL_PIN(202, (char *)"SNDW2_CLK"),
    PINCTRL_PIN(203, (char *)"SNDW2_DATA"),
    PINCTRL_PIN(204, (char *)"SNDW3_CLK"),
    PINCTRL_PIN(205, (char *)"SNDW3_DATA"),
    PINCTRL_PIN(206, (char *)"SNDW4_CLK"),
    PINCTRL_PIN(207, (char *)"SNDW4_DATA"),
    /* GPP_E */
    PINCTRL_PIN(208, (char *)"SATAXPCIE_0"),
    PINCTRL_PIN(209, (char *)"SATAXPCIE_1"),
    PINCTRL_PIN(210, (char *)"SATAXPCIE_2"),
    PINCTRL_PIN(211, (char *)"CPU_GP_0"),
    PINCTRL_PIN(212, (char *)"SATA_DEVSLP_0"),
    PINCTRL_PIN(213, (char *)"SATA_DEVSLP_1"),
    PINCTRL_PIN(214, (char *)"SATA_DEVSLP_2"),
    PINCTRL_PIN(215, (char *)"CPU_GP_1"),
    PINCTRL_PIN(216, (char *)"SATA_LEDB"),
    PINCTRL_PIN(217, (char *)"USB2_OCB_0"),
    PINCTRL_PIN(218, (char *)"USB2_OCB_1"),
    PINCTRL_PIN(219, (char *)"USB2_OCB_2"),
    PINCTRL_PIN(220, (char *)"USB2_OCB_3"),
    PINCTRL_PIN(221, (char *)"SPI1_CSB"),
    PINCTRL_PIN(222, (char *)"SPI1_CLK"),
    PINCTRL_PIN(223, (char *)"SPI1_MISO_IO_1"),
    PINCTRL_PIN(224, (char *)"SPI1_MOSI_IO_0"),
    PINCTRL_PIN(225, (char *)"SPI1_IO_2"),
    PINCTRL_PIN(226, (char *)"SPI1_IO_3"),
    PINCTRL_PIN(227, (char *)"GPP_E_19"),
    PINCTRL_PIN(228, (char *)"GPP_E_20"),
    PINCTRL_PIN(229, (char *)"ISH_UART0_CTSB"),
    PINCTRL_PIN(230, (char *)"SPI1_CLK_LOOPBK"),
    /* GPP_K */
    PINCTRL_PIN(231, (char *)"GSXDOUT"),
    PINCTRL_PIN(232, (char *)"GSXSLOAD"),
    PINCTRL_PIN(233, (char *)"GSXDIN"),
    PINCTRL_PIN(234, (char *)"GSXSRESETB"),
    PINCTRL_PIN(235, (char *)"GSXCLK"),
    PINCTRL_PIN(236, (char *)"ADR_COMPLETE"),
    PINCTRL_PIN(237, (char *)"GPP_K_6"),
    PINCTRL_PIN(238, (char *)"GPP_K_7"),
    PINCTRL_PIN(239, (char *)"CORE_VID_0"),
    PINCTRL_PIN(240, (char *)"CORE_VID_1"),
    PINCTRL_PIN(241, (char *)"GPP_K_10"),
    PINCTRL_PIN(242, (char *)"GPP_K_11"),
    PINCTRL_PIN(243, (char *)"SYS_PWROK"),
    PINCTRL_PIN(244, (char *)"SYS_RESETB"),
    PINCTRL_PIN(245, (char *)"MLK_RSTB"),
    /* GPP_F */
    PINCTRL_PIN(246, (char *)"SATAXPCIE_3"),
    PINCTRL_PIN(247, (char *)"SATAXPCIE_4"),
    PINCTRL_PIN(248, (char *)"SATAXPCIE_5"),
    PINCTRL_PIN(249, (char *)"SATAXPCIE_6"),
    PINCTRL_PIN(250, (char *)"SATAXPCIE_7"),
    PINCTRL_PIN(251, (char *)"SATA_DEVSLP_3"),
    PINCTRL_PIN(252, (char *)"SATA_DEVSLP_4"),
    PINCTRL_PIN(253, (char *)"SATA_DEVSLP_5"),
    PINCTRL_PIN(254, (char *)"SATA_DEVSLP_6"),
    PINCTRL_PIN(255, (char *)"SATA_DEVSLP_7"),
    PINCTRL_PIN(256, (char *)"SATA_SCLOCK"),
    PINCTRL_PIN(257, (char *)"SATA_SLOAD"),
    PINCTRL_PIN(258, (char *)"SATA_SDATAOUT1"),
    PINCTRL_PIN(259, (char *)"SATA_SDATAOUT0"),
    PINCTRL_PIN(260, (char *)"PS_ONB"),
    PINCTRL_PIN(261, (char *)"M2_SKT2_CFG_0"),
    PINCTRL_PIN(262, (char *)"M2_SKT2_CFG_1"),
    PINCTRL_PIN(263, (char *)"M2_SKT2_CFG_2"),
    PINCTRL_PIN(264, (char *)"M2_SKT2_CFG_3"),
    PINCTRL_PIN(265, (char *)"L_VDDEN"),
    PINCTRL_PIN(266, (char *)"L_BKLTEN"),
    PINCTRL_PIN(267, (char *)"L_BKLTCTL"),
    PINCTRL_PIN(268, (char *)"VNN_CTRL"),
    PINCTRL_PIN(269, (char *)"GPP_F_23"),
    /* GPP_D */
    PINCTRL_PIN(270, (char *)"SRCCLKREQB_0"),
    PINCTRL_PIN(271, (char *)"SRCCLKREQB_1"),
    PINCTRL_PIN(272, (char *)"SRCCLKREQB_2"),
    PINCTRL_PIN(273, (char *)"SRCCLKREQB_3"),
    PINCTRL_PIN(274, (char *)"SML1CLK"),
    PINCTRL_PIN(275, (char *)"I2S2_SFRM"),
    PINCTRL_PIN(276, (char *)"I2S2_TXD"),
    PINCTRL_PIN(277, (char *)"I2S2_RXD"),
    PINCTRL_PIN(278, (char *)"I2S2_SCLK"),
    PINCTRL_PIN(279, (char *)"SML0CLK"),
    PINCTRL_PIN(280, (char *)"SML0DATA"),
    PINCTRL_PIN(281, (char *)"SRCCLKREQB_4"),
    PINCTRL_PIN(282, (char *)"SRCCLKREQB_5"),
    PINCTRL_PIN(283, (char *)"SRCCLKREQB_6"),
    PINCTRL_PIN(284, (char *)"SRCCLKREQB_7"),
    PINCTRL_PIN(285, (char *)"SML1DATA"),
    PINCTRL_PIN(286, (char *)"GSPI3_CS0B"),
    PINCTRL_PIN(287, (char *)"GSPI3_CLK"),
    PINCTRL_PIN(288, (char *)"GSPI3_MISO"),
    PINCTRL_PIN(289, (char *)"GSPI3_MOSI"),
    PINCTRL_PIN(290, (char *)"UART3_RXD"),
    PINCTRL_PIN(291, (char *)"UART3_TXD"),
    PINCTRL_PIN(292, (char *)"UART3_RTSB"),
    PINCTRL_PIN(293, (char *)"UART3_CTSB"),
    PINCTRL_PIN(294, (char *)"GSPI3_CLK_LOOPBK"),
    /* JTAG */
    PINCTRL_PIN(295, (char *)"JTAG_TDO"),
    PINCTRL_PIN(296, (char *)"JTAGX"),
    PINCTRL_PIN(297, (char *)"PRDYB"),
    PINCTRL_PIN(298, (char *)"PREQB"),
    PINCTRL_PIN(299, (char *)"JTAG_TDI"),
    PINCTRL_PIN(300, (char *)"JTAG_TMS"),
    PINCTRL_PIN(301, (char *)"JTAG_TCK"),
    PINCTRL_PIN(302, (char *)"DBG_PMODE"),
    PINCTRL_PIN(303, (char *)"CPU_TRSTB"),
};

static unsigned int adls_i2c0_pins[] = { 192, 193 };
static unsigned int adls_i2c1_pins[] = { 194, 195 };
static unsigned int adls_uart0_pins[] = { 184, 185, 186, 187 };
static unsigned int adls_uart1_pins[] = { 188, 189, 190, 191 };
static unsigned int adls_uart2_pins[] = { 196, 197, 198, 199 };

static struct intel_pingroup adls_groups[] = {
    PIN_GROUP((char *)"i2c0_grp", adls_i2c0_pins, 1),
    PIN_GROUP((char *)"i2c1_grp", adls_i2c1_pins, 1),
    PIN_GROUP((char *)"uart0_grp", adls_uart0_pins, 1),
    PIN_GROUP((char *)"uart1_grp", adls_uart1_pins, 1),
    PIN_GROUP((char *)"uart2_grp", adls_uart2_pins, 1),
};

static char * const adls_i2c0_groups[] = { (char *)"i2c0_grp" };
static char * const adls_i2c1_groups[] = { (char *)"i2c1_grp" };
static char * const adls_uart0_groups[] = { (char *)"uart0_grp" };
static char * const adls_uart1_groups[] = { (char *)"uart1_grp" };
static char * const adls_uart2_groups[] = { (char *)"uart2_grp" };

static struct intel_function adls_functions[] = {
    FUNCTION((char *)"i2c0", adls_i2c0_groups),
    FUNCTION((char *)"i2c1", adls_i2c1_groups),
    FUNCTION((char *)"uart0", adls_uart0_groups),
    FUNCTION((char *)"uart1", adls_uart1_groups),
    FUNCTION((char *)"uart2", adls_uart2_groups),
};

static struct intel_padgroup adls_community0_gpps[] = {
    ADL_S_GPP(0, 0, 24, 0),             /* GPP_I */
    ADL_S_GPP(1, 25, 47, 32),           /* GPP_R */
    ADL_S_GPP(2, 48, 59, 64),           /* GPP_J */
    ADL_S_GPP(3, 60, 86, 96),           /* vGPIO */
    ADL_S_GPP(4, 87, 94, 128),          /* vGPIO_0 */
};

static struct intel_padgroup adls_community1_gpps[] = {
    ADL_S_GPP(0, 95, 118, 160),         /* GPP_B */
    ADL_S_GPP(1, 119, 126, 192),        /* GPP_G */
    ADL_S_GPP(2, 127, 150, 224),        /* GPP_H */
};

static struct intel_padgroup adls_community2_gpps[] = {
    ADL_S_GPP(0, 151, 159, ADL_S_NO_GPIO),  /* SPI0 */
    ADL_S_GPP(1, 160, 175, 256),        /* GPP_A */
    ADL_S_GPP(2, 176, 199, 288),        /* GPP_C */
};

static struct intel_padgroup adls_community3_gpps[] = {
    ADL_S_GPP(0, 200, 207, 320),        /* GPP_S */
    ADL_S_GPP(1, 208, 230, 352),        /* GPP_E */
    ADL_S_GPP(2, 231, 245, 384),        /* GPP_K */
    ADL_S_GPP(3, 246, 269, 416),        /* GPP_F */
};

static struct intel_padgroup adls_community4_gpps[] = {
    ADL_S_GPP(0, 270, 294, 448),        /* GPP_D */
    ADL_S_GPP(1, 295, 303, ADL_S_NO_GPIO),  /* JTAG */
};

static struct intel_community adls_communities[] = {
    ADL_S_COMMUNITY(0, 0, 94, adls_community0_gpps),
    ADL_S_COMMUNITY(1, 95, 150, adls_community1_gpps),
    ADL_S_COMMUNITY(2, 151, 199, adls_community2_gpps),
    ADL_S_COMMUNITY(3, 200, 269, adls_community3_gpps),
    ADL_S_COMMUNITY(4, 270, 303, adls_community4_gpps),
};

class VoodooGPIOAlderLakeS : public VoodooGPIOIntel {
    OSDeclareDefaultStructors(VoodooGPIOAlderLakeS);

    bool start(IOService *provider) override;
};

#endif /* VoodooGPIOAlderLakeS_hpp */
