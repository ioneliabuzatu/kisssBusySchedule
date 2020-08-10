import yaml
from selenium import webdriver

from defaults import COURSE_SEARCH_PAGE
from defaults import DETAILED_SEARCH
from defaults import ENGLISH_LANGUAGE
from defaults import AI_CURRICULUM
from defaults import SEARCH_BUTTON
from defaults import ALL_AI_COURSES_2020W

driver = webdriver.Chrome('/usr/local/bin/chromedriver')
driver.get('https://www.kusss.jku.at/')

timeout = 10

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

    semester_timetable = set()

    for r, row in enumerate(all_rows):
        if r == 0:
            continue
        else:
            cols_per_row = row.find_elements_by_css_selector("td")
            courseDesiredInfo = []
            for c, col in enumerate(cols_per_row):
                if c == 1:
                    courseDesiredInfo.append(col.text)
                elif c == 2:
                    courseDesiredInfo.append(col.text)
                elif c == 8:
                    courseDesiredInfo.append((col.text.split("\n")[0]))

            semester_timetable.add(tuple(courseDesiredInfo))
            print(semester_timetable)
    return semester_timetable


semester_courses = extract_data()
driver.quit()
with open("./resources/maya.yaml") as yaml_config:
    scraped_data_filename = yaml.load(yaml_config)["saveScrapedDataFilename"]
    with open(f"./resources/scraped-data/{scraped_data_filename}", "w") as file:
        for course in semester_courses:
            course_name, course_type, course_hour = course
            if course_hour != "No dates found":
                file.write(f"{course_name.replace(',', '')}, {course_type}, {course_hour}\n")
