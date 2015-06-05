from flask import Flask, jsonify
from flask.json import JSONEncoder
import datetime

class CustomEncoder(JSONEncoder):
    def default(self, obj):
        if isinstance(obj, datetime.timedelta):
            return str(obj)
        return super(CustomEncoder, self).default(obj)

app = Flask(__name__)
app.debug = True

# Comment out the line below and get serialization error
app.json_encoder = CustomEncoder

@app.route("/")
def index():
    td = datetime.timedelta(seconds=5)
    myobj = {'somekey': td}
    return jsonify(**myobj)

if __name__ == "__main__":
    app.run()
