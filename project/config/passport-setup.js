const passport = require('passport');
const GoogleStrategy = require('passport-google-oauth20');
const keys = require('./keys');
const User = require('../models/user-model');

passport.use(new GoogleStrategy({
    callbackURL:'/auth/google/redirect',
    clientID: keys.google.clientID,
    clientSecret: keys.google.clientSecret
}, (accessToken, refreshToken, profile, done) => {
    console.log('passport callback function - Google');
    // console.log(profile);
    let avatar;
    if (profile.photos != null && profile.photos.length > 0 ) {
        avatar = profile.photos[0].value;
    }

    User.findOne({id: profile.id}).then((savedUser) => {
        // Check if user exist in DB
        if (!savedUser) {
            // Add new user in mongo
            new User({
                id: profile.id,
                org: "Google",
                username: profile.displayName,
                avatar: avatar
            }).save().then((newUser) => {
                console.log(newUser);
            })
        }
    })
}))
