const passport = require('passport');
const GoogleStrategy = require('passport-google-oauth20').Strategy;
const GithubStrategy = require('passport-github2').Strategy;
// const keys = require('./keys');
const User = require('../models/user-model');
require('dotenv').config();

passport.serializeUser((user, done) => {
    done(null, user.id);
});

passport.deserializeUser((id, done) => {
    User.findById(id).then((user) => {
        done(null, user);
    })
});

passport.use(new GoogleStrategy({
    callbackURL: process.env.GOO_callBackURL,
    clientID: process.env.GOO_clientID,
    clientSecret: process.env.GOO_Secret
}, (accessToken, refreshToken, profile, done) => {
    console.log('Google - CallBack function');
    console.log(profile);

    User.findOne({org_id: profile.id}).then((savedUser) => {
        // Check if user exist in DB
        if (!savedUser) {
            let avatar;
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
                console.log("New User Added in mongo! ", newUser);
                done(null, newUser);
            })
        } else {
            // User exist in BD
            console.log("Existent user! ", savedUser);
            done(null, savedUser);
        }
    })
}))

passport.use(new GithubStrategy({
    callbackURL: process.env.GIT_callBackURL,
    clientID: process.env.GIT_clientID,
    clientSecret: process.env.GIT_secretKey
}, (accessToken, refreshToken, profile, done) => {
    console.log('GitHub - CallBack Function!');
    console.log(profile);
    User.findOne({org_id: profile.id}).then((savedUser) => {
        // Check if user exist in DB
        if (!savedUser) {
            let avatar;
            if (profile.photos != null && profile.photos.length > 0 ) {
                avatar = profile.photos[0].value;
            }
            // Add new user in mongo
            new User({
                org_id: profile.id,
                org: profile.provider,
                username: profile.username,
                full_name: profile.displayName,
                avatar: avatar
            }).save().then((newUser) => {
                console.log("New User! ", newUser);
                done(null, newUser);
            })
        } else {
            // User exist in BD
            console.log("Existent user! ", savedUser);
            done(null, savedUser);
        }
    })
}))
