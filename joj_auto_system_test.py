import logger
import requests
from bs4 import BeautifulSoup
from typing import Dict
import time

SID = '' # Check https://github.com/BoYanZh/JI-Auth
URL = 'https://joj.sjtu.edu.cn/d/vg101_fall_2021_jigang/homework/61a0f1a87fe7290007dc0935/system_test'


def create_sess(cookies: Dict[str, str]) -> requests.Session:
    s = requests.Session()
    s.cookies.update(cookies)
    return s


sess = create_sess(
    cookies={"sid": SID, "JSESSIONID": "dummy", "save": "1"}
)
logger = logger
# print(sess.get("https://joj.sjtu.edu.cn/login/jaccount").status_code)
html = sess.get(URL).text
soup = BeautifulSoup(html, features="html.parser")
csrf_token_node = soup.find("input", {"name": "csrf_token"})
csrf_token = csrf_token_node.get("value")
while True:
    response = sess.post(
        URL,
        data={"csrf_token": csrf_token, "judge_category": "pretest, sentence", "system_test_new": True},
    )
    print(response)
    time.sleep(600)

# print(response)

