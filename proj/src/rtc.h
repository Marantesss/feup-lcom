#ifndef _LCOM_RTC_H
#define _LCOM_RTC_H

/** @defgroup rtc rtc
 * @{
 * Part of lab6 and evething needed to make rtc put in the struc Minix force
 * the right values for The hour, minute, second and day, month and year.
 */

/**
 * @brief 
 * struct that contain the
 * right values for The hour, minute, second and day, month and year.
 */
typedef struct {
  	unsigned int day;	/**< @brief day of the month */
	unsigned int month; /**< @brief month of the year */
	unsigned int year;	/**< @brief the last digits of the year */
	unsigned int hour;  /**< @brief hour */
	unsigned int min; 	/**< @brief minutes */
	unsigned int sec;	/**< @brief seconds */
	
} rtc_time_t;

/**
 * @brief Subscribes and enables RTC interrupts
 *
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_subscribe_int (uint8_t *bit_no);

/**
 * @brief Unsubscribes RTC interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_unsubscribe_int ();

/**
 * @brief 
 * See in which state rtc is on updates.
 * If it is, is possible that the information is not valid.
 * 
 * @return if the information is valid ou if can not be valid
 */
int isValid_rtc();
/**
 * @brief 
 * Function of lab6. It is not used in the project.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_test_conf();

/**
 * @brief 
 * clear the C register of the RTC ir order to allow other interrupts to come.
 *
 */
void clear_regC();

/**
 * @brief 
 * Enables update interrupts in the control register of the RTC.
 *
 */
void enable_interrupts_();

/**
 * @brief 
 * Disables update interrupts in the control register of the RTC.
 *
 */
void disable_interrupts_();

/**
 * @brief 
 * Converts a number in binary codification to decimal.
 * @param number in binary
 * @return the converted number in decima
 */
int bcd_to_decimal(uint32_t x);

/**
 * @brief 
 * Reads the right values for the day, month and year and puts them in the
 * declared parametres of the struct Minixforce. In the struct, values are decimal.
 * @note If the millenium changes, change the macro.
 */
void rtc_Date();

/**
 * @brief 
 * Reads the right values for the mand puts them in the hour, minute and second to the
 * declared parametres of the struct Minixforce. In the struct, values are decimal.
 * @note If the millenium changes, change the macro.
 */
void rtc_Time();

/**
 * @brief 
 * Starts by clear register C. \n
 * Calls a function that puts the right values for the hour, minute, second and day, month and year and puts them in the
 * initialezed struct Minixforce.In the struct, values are decimal.
 */ 
void rtc_ih();

/**@}*/

#endif /*_LCOM_RTC_H*/
