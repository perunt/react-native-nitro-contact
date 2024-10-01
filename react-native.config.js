 const path = require('path');
 const pak = require('./modules/contact/package.json');

module.exports = {
  dependencies: {
     [pak.name]: {
       root: path.join(__dirname, 'modules', 'contact'),
    },
  },
};

