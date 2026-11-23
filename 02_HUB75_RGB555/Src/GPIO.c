#include  "GPIO.h"


//GPIO口初始化
void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能 GPIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    // 初始化数据线（GPIOA）
    GPIO_InitStructure.GPIO_Pin = R1_PIN | G1_PIN | B1_PIN | R2_PIN | G2_PIN | B2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DATA_PORT, &GPIO_InitStructure);

    // 初始化地址线（GPIOB）
    GPIO_InitStructure.GPIO_Pin = A_PIN | B_PIN | C_PIN | D_PIN;
    GPIO_Init(ADDR_PORT, &GPIO_InitStructure);

    // 初始化控制线（GPIOB）
    GPIO_InitStructure.GPIO_Pin = CLK_PIN | LAT_PIN | OE_PIN;
    GPIO_Init(CTRL_PORT, &GPIO_InitStructure);

    // 设置所有引脚初始状态
    GPIO_ResetBits(DATA_PORT, R1_PIN | G1_PIN | B1_PIN | R2_PIN | G2_PIN | B2_PIN);
    GPIO_ResetBits(ADDR_PORT, A_PIN | B_PIN | C_PIN | D_PIN);
    GPIO_ResetBits(CTRL_PORT, CLK_PIN | LAT_PIN);
    GPIO_SetBits(CTRL_PORT, OE_PIN); // 禁用显示
}
