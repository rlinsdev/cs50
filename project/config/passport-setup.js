const passport = require('passport');
const GoogleStrategy = require('passport-google-oauth20').Strategy;
const keys = require('./keys');
const User = require('../models/user-model');

passport.serializeUser((user, done) => {
    done(null, user.id);
});

passport.deserializeUser((id, done) => {
    User.findById(id).then((user) => {
        done(null, user);
    })
});

passport.use(new GoogleStrategy({
    callbackURL:'/auth/google/redirect',
    clientID: keys.google.clientID,
    clientSecret: keys.google.clientSecret
}, (accessToken, refreshToken, profile, done) => {
    // console.log('passport callback function - Google');
    // console.log(profile);

    User.findOne({id: profile.id}).then((savedUser) => {
        // Check if user exist in DB
        if (!savedUser) {
            let avatar;
            console.log(profile);
            if (profile.photos != null && profile.photos.length > 0 ) {
                avatar = profile.photos[0].value;
            }
            // Add new user in mongo
            new User({
                org_id: profile.id,
                org: "Google",
                username: profile.displayName,
                avatar: avatar
            }).save().then((newUser) => {
                // console.log("New User! ", newUser);
                done(null, newUser);
            })
        } else {
            // User exist in BD
            // console.log("Existent user! ", savedUser);
            done(null, savedUser);
        }
    })
}))
