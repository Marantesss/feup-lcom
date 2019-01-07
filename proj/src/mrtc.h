#ifndef _LCOM_MRTC_H
#define _LCOM_MRTC_H


/** @defgroup mrtc mrtc
 * @{
 *
 * Constants for programming RTC.
 */

#define BIT(n)              (0x01<<(n))

#define RTC_IRQ       8
#define MILLENUIM     2000

/********************************/
/**********ADDRESSES ************/
/********************************/

#define RTC_ADDR_REG          0x70    /**< @brief address of the RTC register to be accessed */
#define RTC_DATA_REG          0x71    /**< @brief used to transfer the data to/from RTC register */

#define RTC_SECONDS 	    	0   /**< @brief address of RTC's seconds register */
#define RTC_MINUTES 	    	2   /**< @brief address of RTC's minutes register */
#define RTC_HOURS 		    	4   /**< @brief address of RTC's hour register  */
#define RTC_DAYOFWEEK 	        6   /**< @brief address of RTC's days of week register  */
#define RTC_DAYOFMONTH        	7   /**< @brief address of RTC's days of month register */
#define RTC_MONTH			    8   /**< @brief address of RTC's month register  */
#define RTC_YEAR			    9   /**< @brief address of RTC's year register */

#define RTC_REG_A	    	    10 /**< @brief RTC's A register address */
#define RTC_REG_B		        11 /**< @brief RTC's B register address */
#define RTC_REG_C	         	12 /**< @brief RTC's C register address */
#define RTC_REG_D	         	13 /**< @brief RTC's D register address */

#define RTC_UIP                 BIT(7)

/**@}*/

#endif
