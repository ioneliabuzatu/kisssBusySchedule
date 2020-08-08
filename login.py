from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.common.by import By

from defaults import COURSE_SEARCH_PAGE
from defaults import DETAILED_SEARCH
from defaults import ENGLISH_LANGUAGE
from defaults import AI_CURRICULUM
from defaults import SEARCH_BUTTON
from defaults import ALL_AI_COURSES_2020W

driver = webdriver.Chrome('/usr/local/bin/chromedriver')
driver.get('https://www.kusss.jku.at/')

timeout = 10

try:
    # element = wait.until(EC.element_to_be_clickable((By.XPATH, "//div[@class='content' and text()='Load More']")))
    WebDriverWait(driver, timeout).until(expected_conditions.visibility_of_element_located((By.ID, "productTitle")))
except TimeoutException:
    print('Timed out waiting for page to load')
    driver.quit()

username = input()
password = input()

driver.find_element_by_id("j_username").send_keys(username)
driver.find_element_by_id("j_password").send_keys(password)
driver.find_element_by_class_name("submit").click()
driver.find_element_by_xpath(COURSE_SEARCH_PAGE).click()
driver.find_element_by_xpath(DETAILED_SEARCH).click()
driver.find_element_by_xpath(ENGLISH_LANGUAGE).click()
driver.find_element_by_xpath(AI_CURRICULUM).click()
driver.find_element_by_xpath(SEARCH_BUTTON).click()

all_rows = driver.find_elements_by_xpath(ALL_AI_COURSES_2020W)


def extract_data():
    """
    item from table->first row and first col text
    :return: semester_timetable
    """

    semester_timetable = None

    for i, row in enumerate(all_rows):
        if i == 0:
            continue
        else:
            print(row.find_element_by_css_selector("td[align='center']").text)
            cols_per_row = row.find_elements_by_css_selector("td")
            print(len(cols_per_row))
            for col in cols_per_row:
                print(col.text)
