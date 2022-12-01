from flask import Flask
import smtplib, ssl
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

app = Flask(__name__)

receiver_email = '9165916384@vzwpix.com'
sender_email   = 'cs530projectsender@gmail.com'
password       = 'klqlntpiezdcczwx'

reenable = 'You have reenabled the lock.'
unlock_body = 'The lock has been unlocked!'
disable = 'A password attempt failed!\nThe lock has been disabled!'
failed_attempt = 'A password attempt failed!'
at_door = 'Someone is at your door.'

def text(receiver_email, sender_email, password, body):
    port = 587  # For starttls
    smtp_server = "smtp.gmail.com"
    subject = "Wireless Lock"
    message = MIMEMultipart('alternative')
    message['From'] = sender_email.split('@')[0] + f' <{sender_email}>'
    message['Subject'] = subject
    message.attach(MIMEText(body))
    text = message.as_string()
    context = ssl.create_default_context()
    with smtplib.SMTP(smtp_server, port) as server:
        server.ehlo()  # Can be omitted
        server.starttls(context=context)
        server.ehlo()  # Can be omitted
        server.login(sender_email, password)
        server.sendmail(sender_email, receiver_email, text)

        print("Texted")
        return

@app.route("/")
def hello_world():
    return "<p>Hello World!</p>"

@app.route("/lock")
def lock():
    text(receiver_email, sender_email, password)
    return "<p>Lock</p>"