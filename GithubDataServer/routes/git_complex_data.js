var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
    res.render('git_complex_data_display', {});
});

module.exports = router;
