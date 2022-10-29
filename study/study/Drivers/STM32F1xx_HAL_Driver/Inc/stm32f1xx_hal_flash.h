/**
  ******************************************************************************
  * @file    stm32f1xx_hal_flash.h
  * @author  MCD Application Team
  * @brief   Header file of Flash HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1xx_HAL_FLASH_H
#define __STM32F1xx_HAL_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"
   
/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */
  
/** @addtogroup FLASH_Private_Constants
  * @{
  */
#define FLASH_TIMEOUT_VALUE              50000U /* 50 s */
/**
  * @}
  */

/** @addtogroup FLASH_Private_Macros
  * @{
  */

#define IS_FLASH_TYPEPROGRAM(VALUE)  (((VALUE) == FLASH_TYPEPROGRAM_HALFWORD) || \
                                      ((VALUE) == FLASH_TYPEPROGRAM_WORD)     || \
                                      ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD))  

#if   defined(FLASH_ACR_LATENCY)
#define IS_FLASH_LATENCY(__LATENCY__) (((__LATENCY__) == FLASH_LATENCY_0) || \
                                       ((__LATENCY__) == FLASH_LATENCY_1) || \
                                       ((__LATENCY__) == FLASH_LATENCY_2))

#else
#define IS_FLASH_LATENCY(__LATENCY__)   ((__LATENCY__) == FLASH_LATENCY_0)
#endif /* FLASH_ACR_LATENCY */
/**
  * @}
  */  

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */  

/**
  * @brief  FLASH Procedure structure definition
  */
typedef enum 
{
  FLASH_PROC_NONE              = 0U, 
  FLASH_PROC_PAGEERASE         = 1U,
  FLASH_PROC_MASSERASE         = 2U,
  FLASH_PROC_PROGRAMHALFWORD   = 3U,
  FLASH_PROC_PROGRAMWORD       = 4U,
  FLASH_PROC_PROGRAMDOUBLEWORD = 5U
} FLASH_ProcedureTypeDef;

/** 
  * @brief  FLASH handle Structure definition  
  */
typedef struct
{
  __IO FLASH_ProcedureTypeDef ProcedureOnGoing; /*!< Internal variable to indicate which procedure is ongoing or not in IT context */
  
  __IO uint32_t               DataRemaining;    /*!< Internal variable to save the remaining pages to erase or half-word to program in IT context */

  __IO uint32_t               Address;          /*!< Internal variable to save address selected for program or erase */

  __IO uint64_t               Data;             /*!< Internal variable to save data to be programmed */

  HAL_LockTypeDef             Lock;             /*!< FLASH locking object                */

  __IO uint32_t               ErrorCode;        /*!< FLASH error code                    
                                                     This parameter can be a value of @ref FLASH_Error_Codes  */
} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */  

/** @defgroup FLASH_Error_Codes FLASH Error Codes
  * @{
  */

#define HAL_FLASH_ERROR_NONE      0x00U  /*!< No error */
#define HAL_FLASH_ERROR_PROG      0x01U  /*!< Programming error */
#define HAL_FLASH_ERROR_WRP       0x02U  /*!< Write protection error */
#define HAL_FLASH_ERROR_OPTV      0x04U  /*!< Option validity error */

/**
  * @}
  */

/** @defgroup FLASH_Type_Program FLASH Type Program
  * @{
  */ 
#define FLASH_TYPEPROGRAM_HALFWORD             0x01U  /*!<Program a half-word (16-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_WORD                 0x02U  /*!<Program a word (32-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_DOUBLEWORD           0x03U  /*!<Program a double word (64-bit) at a specified address*/

/**
  * @}
  */

#if   defined(FLASH_ACR_LATENCY)
/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0            0x00000000U               /*!< FLASH Zero Latency cycle */
#define FLASH_LATENCY_1            FLASH_ACR_LATENCY_0       /*!< FLASH One Latency cycle */
#define FLASH_LATENCY_2            FLASH_ACR_LATENCY_1       /*!< FLASH Two Latency cycles */

/**
  * @}
  */

#else
/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define FLASH_LATENCY_0            0x00000000U    /*!< FLASH Zero Latency cycle */

/**
  * @}
  */

#endif /* FLASH_ACR_LATENCY */
/**
  * @}
  */  
  
/* Exported macro ------------------------------------------------------------*/

/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
 *  @brief macros to control FLASH features 
 *  @{
 */
 
/** @defgroup FLASH_Half_Cycle FLASH Half Cycle
 *  @brief macros to handle FLASH half cycle
 * @{
 */

/**
  * @brief  Enable the FLASH half cycle access.
  * @note   half cycle access can only be used with a low-frequency clock of less than
            8 MHz that can be obtained with the use of HSI or HSE but not of PLL.
  * @retval None
  */
#define __HAL_FLASH_HALF_CYCLE_ACCESS_ENABLE()  (FLASH->ACR |= FLASH_ACR_HLFCYA)

/**
  * @brief  Disable the FLASH half cycle access.
  * @note   half cycle access can only be used with a low-frequency clock of less than
            8 MHz that can be obtained with the use of HSI or HSE but not of PLL.
  * @retval None
  */
#define __HAL_FLASH_HALF_CYCLE_ACCESS_DISABLE() (FLASH->ACR &= (~FLASH_ACR_HLFCYA))

/**
  * @}
  */

#if defined(FLASH_ACR_LATENCY)
/** @defgroup FLASH_EM_Latency FLASH Latency
 *  @brief macros to handle FLASH Latency
 * @{
 */ 
  
/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__ FLASH Latency                   
  *         The value of this parameter depend on device used within the same series
  * @retval None
  */ 
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    (FLASH->ACR = (FLASH->ACR&(~FLASH_ACR_LATENCY)) | (__LATENCY__))


/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency                   
  *         The value of this parameter depend on device used within the same series
  */ 
#define __HAL_FLASH_GET_LATENCY()     (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY))

/**
  * @}
  */

#endif /* FLASH_ACR_LATENCY */
/** @defgroup FLASH_Prefetch FLASH Prefetch
 *  @brief macros to handle FLASH Prefetch buffer
 * @{
 */   
/**
  * @brief  Enable the FLASH prefetch buffer.
  * @retval None
  */ 
#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()    (FLASH->ACR |= FLASH_ACR_PRFTBE)

/* - 쉽게 분석하는법 -
 * 1. 일단 실행문을 메모장에 복사한다.
 * 2. FLASH 등의 의미를 알기 위해 게속 따라간다.
 * 3. 그럼 다시 FLASH_R_BASE 등의 모르겠는 변수가 나타난다.
 * 4. 의미를 알 때 까지 반복한다. 나오지 않으면 Ctrl+h를 눌러서 찾는다. ( 리눅스에서의 grep 명령어와 유사 )
 *
 * - 이것을 가장 쉽게 알 수 있는 방법 -
 * 1. FLASH를 복사해서 우측 변수값 확인에서 Expression에 붙여 넣는다.
 * 2. Value에 값이 바로 나오는 걸 확인할 수 있다.
 *
 * - 그래서 FLASH는 무엇이냐? -
 * 1. FLASH_Typedef 라는 구조체 변수 타입. 16진수 0x40022000 가 저장되어 있다. ( 바이트 값 )
 * 2. ACR-0번지, KEYR-4번지, OPTKEYR- 8번지, SR-12번지, CR-16번지, AR-20번지, RESERVED-24번지, OBR-28번지, WRPR-32번지
 * 3. 나는 OBR 세팅 하고싶다면, FLASH->OBR|=4; 와 같이 비트 연산으로 수행
 * 4. FLASH->ACR의 주소는 40022000, FLASH->KEYR의 주소는 40022004, ...
 *
 * - 그 외 -
 * 1. uint32_t = unsigned int
 * 2. __IO = volatile 로 각각 정의되어있다.
 * 3. volatile은 왜 쓰는가?
 * 4. -> 최적화를 방지하기 위함
 * 5. 컴파일러는 최적화라는 것을 한다.
 * 6. GPIO를 제어하는 과정에서 어떤 변수의 값을 자주 바꾼다면...
 * 7. 최적화 과정에서 중간 과정은 모두 생략되고, 마지막 저장 코드만 남겨둔다.
 *
 * -> 결론 : #define __IO volatile 라는 걸 이용해서 CPU에게 최적화를 하지말라는 의미.
 * 			+ 이 변수를 CPU 레지스터에 넣어서 최적화해서 사용하지마.. 무조건 메모리 번지에 올려서 사용해! 라는 의미
 *
 *
 *
 * - 그래서 (FLASH->ACR |= FLASH_ACR_PRFTBE) 가 뭔데? -
 * 1. *(40022000) |= 16;  더라...
 * 2. volatile unsigned int * reg = 40022000; *reg |= 16; 과 같다.
 * 3. FLASH_ACR_PRFTBE 는 1<<4U  ( 1을 unsigned 4 만큼 비트 레프트 시프트 )
 * 4. 레퍼런스 매뉴얼에서 ACR를 검색하며 찾아봤을 때, ACR은 prefetch를 활성화/비활성화 하는 데 사용되는 것으로 유추.
 * 5. 그 중 PRFTBE 비트는 Prefetch 활성화/비활성화를 의미하는 비트
 * 6. FLASH_ACR 레지스터에서 5번째 비트인 PRFTBE 값을 1로 세팅함으로써 Prefetch is enabled ( 레퍼런스 매뉴얼에 써있음 )
 * 7. 즉, 이 작업은 플래시 메모리의 프리패치 기능을 활성화 한 것이구나!!
 * 8. 근데... 영어를 알아도 위 문장이 이해가 안돼.....
 * 9. 여기부터는 컴퓨터의 영역. 백그라운드 지식이다.
 * 10. 플래시 프리패치를 구글에 검색해보자.
 * 11. 각 부품마다 속도 차이가 있으며 CPU가 가장 빠름.
 * 12. CPU 내부에 레지스터, 램, 하드 디스크 등이 있다.
 * 13. 컴퓨터를 키면 하드 디스크에 있는 윈도우의 메모리가 램으로 올라온다. -> 실행할수 있는 단계.. Process 다.
 * 14. 자주 사용되는 건 CPU가 바로 접근하게 레지스터에 등록해서 사용한다.
 * 15. CPU가 램에 접근하는게 선이 몇가닥이냐에 따라 32bit냐 16bit냐 이렇게 정해진다.
 * 16. 가장 느린구간은 램과 하드디스크.. 암튼 겁나 느림
 * 17. 우리가 쓸 건 플래쉬 메모리인데 플래쉬 메모리에 있는 것을 가져와서 빠르게 실행하게 위한 기능이 Prefetch 인가 보다.
 * 18. 결국 중요한 내공은 하드웨어를 알아야 하고 운영체제를 알아야 하는 것이구나..
 *
 *
 */


/**
  * @brief  Disable the FLASH prefetch buffer.
  * @retval None
  */
#define __HAL_FLASH_PREFETCH_BUFFER_DISABLE()   (FLASH->ACR &= (~FLASH_ACR_PRFTBE))

/**
  * @}
  */
  
/**
  * @}
  */ 

/* Include FLASH HAL Extended module */
#include "stm32f1xx_hal_flash_ex.h"  

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */
  
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

/* FLASH IRQ handler function */
void       HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */ 
void       HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void       HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
void HAL_FLASH_OB_Launch(void);

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
  */
/* Peripheral State and Error functions ***************************************/
uint32_t HAL_FLASH_GetError(void);

/**
  * @}
  */

/**
  * @}
  */

/* Private function -------------------------------------------------*/
/** @addtogroup FLASH_Private_Functions
 * @{
 */
HAL_StatusTypeDef       FLASH_WaitForLastOperation(uint32_t Timeout);
#if defined(FLASH_BANK2_END)
HAL_StatusTypeDef       FLASH_WaitForLastOperationBank2(uint32_t Timeout);
#endif /* FLASH_BANK2_END */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

