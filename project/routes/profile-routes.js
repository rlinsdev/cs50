const router = require('express').Router();

// Profile just accessible if user is logged
const authCheck = (req, res, next) => {
    if (!req.user) {
        // rollback to login route
        res.redirect('/auth/login');
    } else {
        // keep going
        next();
    }
}

// Just render profile if user is authenticated
router.get('/', authCheck, (req, res) => {
    res.render('profile', { user: req.user });
});

module.exports = router;
