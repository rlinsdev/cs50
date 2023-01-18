const mongoose = require ('mongoose');
const Schema = mongoose.Schema;

// User Schema in DB
const userSchema = new Schema({
    username: String,
    org: String,
    org_id: String,
    avatar: String,
    full_name: String
});

const User = mongoose.model('user', userSchema);

module.exports = User;
