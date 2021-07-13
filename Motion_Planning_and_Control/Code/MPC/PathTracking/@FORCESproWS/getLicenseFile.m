function getLicenseFileResult = getLicenseFile(obj,userID,license_file_name,database)
%getLicenseFile(obj,userID,license_file_name,database)
%
%     Input:
%       userID = (string)
%       license_file_name = (string)
%       database = (string)
%
%     Output:
%       getLicenseFileResult = (string)

% Build up the argument lists.
values = { ...
   userID, ...
   license_file_name, ...
   database, ...
   };
names = { ...
   'userID', ...
   'license_file_name', ...
   'database', ...
   };

types = { ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   };
 % Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'FORCESPro', ...
    'getLicenseFile', ...
    values,names,types,'document');
response = callSoapService( ...
    obj.endpoint, ...
    'FORCESPro/getLicenseFile', ...
    soapMessage);
getLicenseFileResult = parseSoapResponse(response);
